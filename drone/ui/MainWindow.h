#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

#include "../../../common/include/desktopapp.h"
#include "../../../common/include/desktopui.h"

#include "../include/drone.h"
#include "../include/joystick.h"
#include "../include/controlthread.h"

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

protected:
    void closeEvent(QCloseEvent *event);

private:
    ComPortWidget * wComport;
    QPushButton * bConnect;
    QLabel *lStatusBar;

    Drone* mDrone;
    ControlThread* mControl;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
