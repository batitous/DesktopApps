#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtCore/QDebug>

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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::bTestEvent(void)
{
    mDrone->send(DRONE_CMD_PING);
}

void MainWindow::bConnectEvent(void)
{
    qDebug() << "MainWindow::bConnectEvent" << DesktopApp::portComFromSettings();


    mDrone->connect();

    lStatusBar->setText("Connected");
}

void MainWindow::bClearEvent(void)
{
    qDebug() << "MainWindow::bClearEvent";

    ui->pOutput->clear();
}

