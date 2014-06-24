/* The MIT License (MIT)
 
 Copyright (c) 2014 Baptiste Burles, Kliplab
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of
 this software and associated documentation files (the "Software"), to deal in
 the Software without restriction, including without limitation the rights to
 use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 the Software, and to permit persons to whom the Software is furnished to do so,
 subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 
 */
#ifndef QUEUE_H
#define QUEUE_H

#include <stdint.h>
#include <iostream>

using namespace std;

/**
 * A queue object
 */
template<class QueueType>
class Queue
{
public:

    /**
     * @brief Create a new Queue object
     * @param buffer    Storing's buffer
     * @param size_t    Size of buffer
     */
    Queue(QueueType* buffer, uint32_t size)
    {
        mHead = 0;
        mTail = 0;
        mSize = size;
        mPending = buffer;
    }

    /**
     * @brief Reset the internal state of the queue
     */
    void reset()
    {
        mHead = 0;
        mTail = 0;
    }

    /**
     * @brief Get number of element in queue
     * @return
     */
    uint32_t elementNumber()
    {
        return mTail - mHead;
    }

    /**
     * @brief Write a value into the queue
     * @param value     Value to be written
     * @return False if queue full
     */
    bool write(QueueType value)
    {
        uint32_t size = mSize-1;
        if ( ((mTail+1) & (size)) == ((mHead) & (size)) )
        {
            qDebug() << "Queue::write full !";
            return false;
        }

        mPending[mTail & (size)] = value;
        mTail++;

        return true;
    }

    /**
     * @brief Read a value from the queue
     * @param value     Pointer to a value
     * @return false if queue empty
     */
    bool read(QueueType* value)
    {
        if (mHead == mTail)
        {
            return false;
        }

        *value= mPending[mHead & (mSize-1)];
        mHead++;

        return true;
    }

    /**
     * @brief Read multiple values from the queue
     * @param array     Array where store the values
     * @param want      Number of values to be read
     */
    void read(QueueType *array, uint32_t want)
    {
        QueueType * ptr = array;
        uint32_t size = mSize -1;
        for(uint32_t i=0;i<want;i++)
        {
            *ptr = mPending[mHead & (size)];
            ptr++;
            mHead++;
        }
    }

private:
    uint32_t    mHead;  /**< queue head */
    uint32_t    mTail;  /**< queue tail */
    uint32_t    mSize;  /**< queue size */
    QueueType*  mPending;   /**< buffer where store the value */

};

#endif // QUEUE_H
