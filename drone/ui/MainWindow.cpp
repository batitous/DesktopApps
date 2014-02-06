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
    QString str;
    mDrone->requestLog(str);
    ui->pOutput->insertPlainText(str);

}

void MainWindow::bTestEvent(void)
{
//    testLog();

    float toto[2];
    toto[0] = 123.456;
    toto[1] = -987.6;

    qDebug() << "==> Write to memory !";

    if (mDrone->write(0x3020, (UInt8*)&toto[0], 8)==false)
    {
        qDebug() << "FAILED TO WRITE DATA TO DRONE!";
    }

    waitMs(400);

    qDebug() << "==> Read from memory !";

    UInt16 size = mDrone->read(0x3024, (UInt8*)&toto[0]);

    qDebug() << "Size received=" << size;
    qDebug() << "Toto" << toto[0] << " next:" << toto[1];

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
