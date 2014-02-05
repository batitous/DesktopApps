#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtCore/QDebug>

#include "../include/math-utils.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Drone");


    wComport = new ComPortWidget(ui->wContainer);
    wComport->refreshPortComList();

    bConnect = new QPushButton("Connect", ui->wContainer);
    bConnect->move(bConnect->pos().x() + wComport->width() + 8, bConnect->pos().y() );

    lStatusBar = new QLabel("Not connected", this);
    lStatusBar->setAlignment(Qt::AlignRight);
    ui->statusbar->insertWidget(0, lStatusBar, 1);

    connect(bConnect, SIGNAL(clicked()), this, SLOT(bConnectEvent()));
    connect(ui->bClear, SIGNAL(clicked()), this, SLOT(bClearEvent()));
    connect(ui->bTest, SIGNAL(clicked()), this, SLOT(bTestEvent()));

    mDrone = new Drone();

    mControl = new ControlThread(mDrone, (OpenGLScene*)ui->graphicsView->scene());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::testLog(void)
{
    if (mDrone->run(DRONE_CMD_LOG_SIZE)==false)
    {
        qDebug() << "MainWindow::testLog failed to execute drone command!";
    }

    if (mDrone->ackPacket()->sizeOfNextPacket != 0)
    {
        qDebug() << "===> Get log content !";

        if (mDrone->request(DRONE_CMD_LOG, mDrone->ackPacket()->sizeOfNextPacket + DRONE_PK_ACK_SIZE)==false)
        {
            qDebug() << "MainWindow::testLog: mDrone->request failed !";
        }

        UInt8 log[512];

        memset(log, 0, 512);

        mDrone->extractContent(log, mDrone->ackPacket()->sizeOfNextPacket );

        QString str((char *)log);

        ui->pOutput->insertPlainText(str);
    }
}

void MainWindow::bTestEvent(void)
{

    if (mDrone->runWithSize(DRONE_CMD_MEMORY, 8)==false)
    {
        qDebug() << "MainWindow::bTestEvent failed to execute drone command!";
    }

    float toto[2];
    toto[0] = 123.456;
    toto[1] = -987.6;

    qDebug() << "==> Write to memory ! float:" << sizeof(float);

    mDrone->writeToMemory(0x3020, (UInt8*)&toto[0], 8);

    waitMs(400);

    qDebug() << "==> Read from memory !";

    if (mDrone->prepareReadFromMemory(0x3024)==false)
    {
        qDebug() << "MainWindow::bTestEvent failed to execute drone command!";
    }



    // test output joystick curve
/*    for(float i=-10; i < 10 ; i++)
    {
        qDebug() << i << joystickCurve(i, 3, 1,-10,10) << joystickCurve(i,5, -2,-10,10) << joystickCurve(i,17,0,-10,10);
    }
*/

}

void MainWindow::bConnectEvent(void)
{
    qDebug() << "MainWindow::bConnectEvent" << DesktopApp::portComFromSettings();

    mDrone->connect();

    mControl->start();

    if (mDrone->connected()==true)
    {
        bConnect->setText("Disconnect");
        lStatusBar->setText("Connected");
    }
    else
    {
        bConnect->setText("Connect");
        lStatusBar->setText("Disconnected");
    }
}

void MainWindow::bClearEvent(void)
{
    qDebug() << "MainWindow::bClearEvent";

    ui->pOutput->clear();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    qDebug() << "MainWindow::closeEvent";

    mControl->stop();

    event->accept();
        //event->ignore();
}
