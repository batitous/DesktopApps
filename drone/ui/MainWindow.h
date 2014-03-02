#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtCore/QTimer>

#include "piddialog.h"

#include "../../../common/include/desktopapp.h"
#include "../../../common/include/desktopui.h"

#include "../include/drone.h"
#include "../include/joystick.h"
#include "../include/controlthread.h"

#include "../include/loopstream.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void testLog();

private slots:
    void bConnectEvent(void);
    void bClearEvent(void);
    void bTestEvent(void);
    void bMotorEvent(void);
    void timerUpdate();
    void bPidEvent(float *, int);
protected:
    void closeEvent(QCloseEvent *event);

private:
    ComPortWidget * wComport;
    QPushButton * bConnect;
    QLabel *lStatusBar;

    Drone* mDrone;
    ControlThread* mControl;

    QTimer *timer;
    LoopStream*     mLoop;

    QGraphicsScene * mControlScene;

    PidDialog*      mPidDialog;

    bool mCommunicate;
    bool mMotor;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
