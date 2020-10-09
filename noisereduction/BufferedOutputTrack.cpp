#include "BufferedOutputTrack.h"
#include <assert.h>

BufferedOutputTrack::BufferedOutputTrack()
    : mLength(0)
{ }

void BufferedOutputTrack::Append(float* buffer, size_t length)
{
    mBuffer.insert(mBuffer.end(), buffer, &buffer[length]);
    mLength += length;
}

void BufferedOutputTrack::SetLength(size_t length)
{
    assert(length <= mLength);
    mLength = length;
}
