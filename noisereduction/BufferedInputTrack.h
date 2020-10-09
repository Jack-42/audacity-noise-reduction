#pragma once

#include "Types.h"

class BufferedInputTrack
{
public:
    BufferedInputTrack(const FloatVector& buffer);
    size_t Length() const { return mBuffer.size(); }
    size_t Read(float* buffer, size_t length);
private:
    FloatVector mBuffer;
    size_t mPosition;
};
