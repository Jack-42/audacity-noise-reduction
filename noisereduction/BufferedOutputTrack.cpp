#include "BufferedOutputTrack.h"
#include <assert.h>
#include <iostream> // TODO: Remove, only debugging

BufferedOutputTrack::BufferedOutputTrack() :
    mLength(0)
{ }

void BufferedOutputTrack::Append(float* buffer, size_t length)
{
    mBuffer.insert(mBuffer.end(), buffer, &buffer[length]);
    mLength += length;
}

void BufferedOutputTrack::SetEnd(size_t newLength)
{
    assert(newLength <= mLength);
    mLength = newLength;
}
