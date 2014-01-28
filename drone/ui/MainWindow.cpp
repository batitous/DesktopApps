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


    connect(bConnect, SIGNAL(clicked()), this, SLOT(bConnectEvent()));
    connect(ui->bClear, SIGNAL(clicked()), this, SLOT(bClearEvent()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::bConnectEvent(void)
{
    qDebug() << "MainWindow::bConnectEvent" << DesktopApp::portComFromSettings();

}

void MainWindow::bClearEvent(void)
{
    qDebug() << "MainWindow::bClearEvent";

    ui->pOutput->clear();
}

