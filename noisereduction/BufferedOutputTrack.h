#pragma once

#include "Types.h"

class BufferedOutputTrack
{
public:
    BufferedOutputTrack();
    void Append(float* buffer, size_t length);
    const FloatVector& Buffer() const { return mBuffer; }
    size_t Length() const { return mLength; }
    void SetLength(size_t length);
private:
    FloatVector mBuffer;
    size_t mLength;
};
