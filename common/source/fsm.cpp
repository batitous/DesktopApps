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

#include "../include/fsm.h"

Fsm::Fsm()
{
    mInit = false;
    mCurrent = 0;
    mOld = 0;
    mCall = 0;
    mInitCall = 0;
}

void Fsm::set(int newstate, FsmCallback call, FsmCallback init)
{
    mCurrent = newstate;
    mCall = call;
    mInitCall = init;
}

void Fsm::init(int state, FsmCallback call, FsmCallback init)
{
    this->set(state, call, init);

    mInit = true;
    mOld = mCurrent;
}

void Fsm::update()
{
    if (mInit == true)
    {
        if (mInitCall != 0)
        {
            (this->*mInitCall)();
        }

        mInit = false;
    }

    if (mCall != 0)
    {
        (this->*mCall)();
    }

    if (mCurrent != mOld)
    {
        mInit = true;
        mOld = mCurrent;
    }
}

bool Fsm::isInState(int state)
{
    if (mCurrent == state)
    {
        return true;
    }

    return false;
}

bool Fsm::isStateInitialized(void)
{
    return mInit;
}

