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
    if (mRun==true)
    {
        mRun = false;
        QThread::msleep(20);
    }
}

void ControlThread::run()
{
    qDebug() << "ControlThread::run is now running !";

    uint32_t begin;
    uint32_t end;

    return;

    Joystick* joystick = Joystick::instance();
    if (joystick==0)
    {
        qDebug() << "ControlThread::run joystick not detected, exit thread!";
        return;
    }

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

    qDebug() << "ControlThread::run, exit thread!";
}
