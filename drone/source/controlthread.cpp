// Baptiste Burles, Kliplab, 2014

#include "../include/controlthread.h"
#include "../include/math-utils.h"

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

        Point3d result;

        result.y = joystickCurve(v.x, 3, 0, -100, 100) *10;
        result.x = joystickCurve(v.y, 3, 0, -100, 100) *10;
        result.z = - joystickCurve(v.z, 3, 0, -100, 100) *10;

        mScene->addRotation(result);

        end = getTicks();

        QThread::msleep(16 - (end-begin));
    }
}
