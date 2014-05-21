// Baptiste Burles, Kliplab, 2014
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
