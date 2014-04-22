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

    mAngleWanted = 0;

    QStringList angleList;
    angleList.append("Angle X");
    angleList.append("Angle Y");
    angleList.append("Angle Z");
    ui->comboAngle->addItems( angleList);

    connect(ui->comboAngle, SIGNAL(activated(int)), this, SLOT(comboAngleEvent(int)) );

    connect(bConnect, SIGNAL(clicked()), this, SLOT(bConnectEvent()));
    connect(ui->bClear, SIGNAL(clicked()), this, SLOT(bClearEvent()));
    connect(ui->bTest, SIGNAL(clicked()), this, SLOT(bTestEvent()));
    connect(ui->bMotor, SIGNAL(clicked()), this, SLOT(bMotorEvent()));

    mDrone = new Drone();
    mCommunicate = false;
    mError = false;

    mControl = new ControlThread(mDrone, (OpenGLScene*)ui->graphicsView->scene());


    QVector <QPointF> points;

    // Fill in points with n number of points
//    for(int i = -200; i< 100; i++)
//       points.append(QPointF(i, i));


    points.append(QPointF(0,0));

    points.append(QPointF(0,100));
    points.append(QPointF(0,250));

    points.append(QPointF(30,30));

    points.append(QPointF(100,30));

    // Create a view, put a scene in it and add tiny circles
    // in the scene

    mControlScene = new QGraphicsScene();

    mControlScene->setSceneRect(-10,-10, 300,300);

    ui->gInstrument->setScene(mControlScene);
    ui->gInstrument->scale(1,-1);


    for(int i = 0; i< points.size(); i++)
    {
        mControlScene->addEllipse(points[i].x(), points[i].y(), 1, 1);

    }

    qDebug() << "Scene rect:" << mControlScene->sceneRect();
    qDebug() << "View  rect:" << ui->gInstrument->sceneRect() << " size:" << ui->gInstrument->size();

    mMotor = false;

    mLoop = new LoopStream(256);
    for(int i=0; i< 256; i++)
    {
        mLoop->write((float)i);
    }

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerUpdate()));
    timer->start(100);


    mPidDialog = new PidDialog(this);
    mPidDialog->show();

    connect(mPidDialog, SIGNAL(sendEvent(float * , int)), this, SLOT(bPidEvent(float *, int)) );
    connect(mPidDialog, SIGNAL(calibEvent(float * , int)), this, SLOT(bCalibEvent(float *, int)) );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::comboAngleEvent(int index)
{
    qDebug() << "==> Set new angle to " << index;
    mAngleWanted = index;
}

void MainWindow::timerUpdate()
{
    //if (mLoop->isAvailable() == true)
    {
        mControlScene->clear();

        float data;
        int i = 0;

        float xprev = 0;
        float yprev = 0;

        while(i<mLoop->mSize)
        {
            data = mLoop->mBuffer[(mLoop->mWrite+i) & (mLoop->mSize-1)];

            mControlScene->addLine( xprev, yprev, i, data);
//            mControlScene->addEllipse(i, data, 1, 1);

            xprev = i;
            yprev = data;

            i++;
        }
        /*while( mLoop->read(&data) == true)
        {
            mControlScene->addEllipse(i, data, 1, 1);

            i++;
        }*/
    }

    if (mDrone->connected()==true)
    {
        float angle[10];
        UInt16 size = 0;

        if (mError==false)
        {
            if (mCommunicate==false)
            {
                mCommunicate = true;

                // yaw & roll & pitch
               //size = mDrone->read(0x4000, (UInt8*)&angle[0]);


                // debug data vector
                 size = mDrone->read(0x9000, (UInt8*)&angle[0]);

                //accel
               //size = mDrone->read(0x6000, (UInt8*)&angle[0]);

                //gyro
                //size = mDrone->read(0x6500, (UInt8*)&angle[0]);

                // pid
    //            size = mDrone->read(0x7000, (UInt8*)&angle[0]);
                if (size != 0)
                {
                    // yaw roll pitch
    //                qDebug() << angle[mAngleWanted];
      //              mLoop->write(angle[mAngleWanted] + 100);

                    // debug data vector
                    qDebug() << angle[mAngleWanted];

    //                angle[mAngleWanted] = angle[mAngleWanted] - 177;
                    mLoop->write(angle[mAngleWanted]*100 + 100 );

                   // angle[mAngleWanted] = angle[mAngleWanted]-300;
                   // mLoop->write(angle[mAngleWanted]*5.0 /*+100*/);


                    // accel
                    //mLoop->write(angle[0]*100 + 100);

                    // gyro
                    //mLoop->write(angle[1] /2 + 100);

                    //pid
                    //mLoop->write(angle[4]+ 100);
                }
                else
                {
                    mError = true;
                }

                mCommunicate = false;
            }
        }
        else
        {
            mError = false;
        }
    }
    else
    {
        //mLoop->write( getRandomBetween(0,100));
    }

    timer->start(33);
}

void MainWindow::bPidEvent(float *coeff, int size)
{
    if (mCommunicate==true)
    {
        return;
    }
    mCommunicate = true;

    qDebug() << "PID size: " << size << " Coeff:" << coeff[0];

    if (mDrone->write(0x8000, (UInt8*)coeff, size)==false)
    {
        qDebug() << "FAILED TO WRITE PID COEFF";
    }

    mCommunicate = false;
}

void MainWindow::bCalibEvent(float *coeff, int size)
{
    if (mCommunicate==true)
    {
        return;
    }
    mCommunicate = true;

    qDebug() << "Calibration angle size: " << size << " Angle:" << coeff[0];

    if (mDrone->write(0x4500, (UInt8*)coeff, size)==false)
    {
        qDebug() << "FAILED TO WRITE ANGLE CALIB";
    }

    mCommunicate = false;
}

void MainWindow::testLog(void)
{
    QString str;
    mDrone->requestLog(str);
    ui->pOutput->insertPlainText(str);

}

void MainWindow::bMotorEvent(void)
{
    UInt32 temp;

    if ( mCommunicate==true)
        return;

    mCommunicate = true;

    if (mMotor==false)
    {
        qDebug() << "RUN";
        temp = 1;
        mDrone->write(0x5000,(UInt8 *)&temp, 4);
        mMotor = true;
    }
    else
    {
        qDebug() << "STOP";
        temp = 0;
        mDrone->write(0x5000,(UInt8 *)&temp, 4);
        mMotor = false;
    }

    mCommunicate = false;
}

void MainWindow::bTestEvent(void)
{




    testLog();

/*
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
