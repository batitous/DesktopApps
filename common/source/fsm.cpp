
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

