#include <iostream>
#include "NoiseReduction.h"
#include "BufferedNoiseReduction.h"
#include "BufferedInputTrack.h"
#include "BufferedOutputTrack.h"
#include "BufferedTrackUtils.h"
#include <sndfile.h>
#include "loguru.hpp"
#include "Utils.h"
#include "cxxopts.hpp"

int main(int argc, char * argv[]) {
    cxxopts::Options options("NoiseReduction Test", "Driver for Noise Reduction");
    options.add_options()
        ("i,input", "Input file (required)", cxxopts::value<std::string>())
        ("o,output", "Output file (required)", cxxopts::value<std::string>())
        ("t0", "Start sample for noise profiling", cxxopts::value<size_t>())
        ("t1", "end sample for noise profiling", cxxopts::value<size_t>())
        ("noiseGain", "Noise Gain (dB)", cxxopts::value<float>()->default_value("12"))
        ("sensitivity", "Sensitivity", cxxopts::value<float>()->default_value("6.0"))
        ("smoothing", "Frequency Smoothing (bands)", cxxopts::value<int>()->default_value("0"))
        ("verbose", "Verbose Output");

    options.parse_positional(std::vector<std::string>{"input", "output"});

    int unparsedArgc = argc;
    auto result = options.parse(unparsedArgc, argv);
    if (!result.count("input") || !result.count("output")) {
        auto help = options.help();
        std::cout << help << std::endl;
        return 1;
    }

    loguru::g_stderr_verbosity = loguru::Verbosity_ERROR;
    if (result["verbose"].count()) {
        loguru::g_stderr_verbosity = loguru::Verbosity_1;
    }

    loguru::init(argc, argv);


    std::cout << "Processing " << result["input"].as<std::string>() << " -> " << result["output"].as<std::string>() << std::endl;

    auto ctx = openAudioFile(result["input"].as<std::string>().c_str());

    NoiseReduction::Settings settings;
    settings.mNewSensitivity = result["sensitivity"].as<float>();
    settings.mFreqSmoothingBands = result["smoothing"].as<int>();
    settings.mNoiseGain = result["noiseGain"].as<float>();

    NoiseReduction reduction(settings, ctx);
    auto t0 = 0;
    auto t1 = ctx.info.frames;

    if (result["t0"].count()) {
        t0 = result["t0"].as<size_t>();
    }

    if (result["t1"].count()) {
        t1 = result["t1"].as<size_t>();
    }

    std::cout << "hello" << std::endl;

#if 0
    std::cout << "Profiling noise..." << std::endl;
    reduction.ProfileNoise(t0, t1);
    std::cout << "Denoising..." << std::endl;
    reduction.ReduceNoise(result["output"].as<std::string>().c_str());
#endif

#if 1
    // TODO: test noise reduction with buffered classes
    // first test: write output track without any change
    std::vector<BufferedInputTrack> inputTracks = BufferedTrackUtils::readTracksFromContext(ctx);
    std::vector<BufferedOutputTrack> outputTracks;
    
    for (const auto& inputTrack : inputTracks) {
        BufferedOutputTrack outputTrack;
        outputTrack.Append((float*)(&(inputTrack.Buffer()[0])), inputTrack.Length());
        outputTracks.push_back(outputTrack);
    }

    const char* outputPath = result["output"].as<std::string>().c_str();
    BufferedTrackUtils::writeTracksToFile(outputPath, outputTracks, ctx.info.channels, ctx.info.samplerate);
#endif

    return 0;
}
