// Baptiste Burles, Kliplab, 2014

#include "../include/controlthread.h"

ControlThread::ControlThread(Drone* pDrone, OpenGLScene* pScene)
{
    mDrone = pDrone;
    mScene = pScene;
    mRun = false;
}

ControlThread::~ControlThread()
{

}

void ControlThread::stop()
{

}

long ControlThread::map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void ControlThread::run()
{
    qDebug() << "ControlThread::run is now running !";

    UInt32 begin;
    UInt32 end;

    Joystick* joystick = Joystick::instance();

    mRun = true;
    while( mRun == true)
    {
        begin = getTicks();

        //end = t + 16; // refresh rate: 60Hz

        joystick->update();

        Point3d v = joystick->values();

        // courbe de Chris


        v.x = map(v.x, -100, 100, -2,2);
        v.y = map(v.y, -100, 100, -2,2);
        v.z = map(v.z, -100, 100, -2,2);

        mScene->addRotation(v);

        end = getTicks();

        QThread::msleep(16 - (end-begin));
    }
}
