
#include <stdlib.h>

#include "../include/loopstream.h"

LoopStream::LoopStream(int pSize)
{
    mRead = 0;
    mWrite = 0;
    mBuffer = (float *)malloc(sizeof(float)*pSize);
    mSize = pSize;
}

LoopStream::~LoopStream()
{

}

void LoopStream::write(float data)
{
    mBuffer[mWrite & (mSize-1)] = data;
    mWrite++;
}

bool LoopStream::isAvailable()
{
    if (mRead != mWrite)
    {
        return true;
    }

    return false;
}

bool LoopStream::read(float *data)
{
    if (mRead != mWrite)
    {
        *data = mBuffer[mRead & (mSize-1)];
        mRead++;
        return true;
    }

    return false;
}
