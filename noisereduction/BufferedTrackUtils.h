#pragma once

#include "Utils.h"
#include "BufferedInputTrack.h"
#include "BufferedOutputTrack.h"

namespace BufferedTrackUtils
{
    std::vector<BufferedInputTrack> readTracksFromContext(const SndContext& ctx, size_t t0 = 0, size_t t1 = 0);
    BufferedInputTrack readOneTrackFromContext(const SndContext &ctx, int channel, size_t t0 = 0, size_t t1 = 0);
    void writeTracksToFile(const std::vector<BufferedOutputTrack> &tracks, const char* path, int channels, int sampleRate);
};
