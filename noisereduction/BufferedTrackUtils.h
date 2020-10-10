#pragma once

#include "Utils.h"
#include "BufferedInputTrack.h"
#include "BufferedOutputTrack.h"
#include <memory>

namespace BufferedTrackUtils
{
    // TODO: add t0 and t1 to only read part of track
    std::vector<BufferedInputTrack> readTracksFromContext(const SndContext& ctx);
    BufferedInputTrack readOneTrackFromContext(const SndContext &ctx, int channel);
    void writeTracksToFile(const std::vector<BufferedOutputTrack> &tracks, const char* path, int channels, int sampleRate);
};
