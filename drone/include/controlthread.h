#ifndef CONTROLTHREAD_H
#define CONTROLTHREAD_H

#include <QtCore/QThread>

#include "gl/openglscene.h"
#include "drone.h"
#include "joystick.h"


class ControlThread : public QThread
{
Q_OBJECT

public:
    ControlThread(Drone* pDrone, OpenGLScene* pScene);
    ~ControlThread();

    void stop();

protected:
    void run();

private:
    OpenGLScene* mScene;
    Drone*      mDrone;
    bool        mRun;

};

#endif // CONTROLTHREAD_H
