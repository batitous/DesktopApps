#include "comportwidget.h"
#include "ui_comportwidget.h"

#include "../include/desktopapp.h"

ComPortWidget::ComPortWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ComPortWidget)
{
    ui->setupUi(this);

    connect(ui->comboBox, SIGNAL(activated(int)), this, SLOT(activatedEvent(int)) );
}

ComPortWidget::~ComPortWidget()
{
    delete ui;
}

void ComPortWidget::refreshPortComList()
{
    QString userComPort = DesktopApp::portComFromSettings();

    Utils::getListOfPortCom(&mPortComList);

    ui->comboBox->clear();
    ui->comboBox->addItems(mPortComList);

    int index = mPortComList.indexOf(userComPort);
    if (index != -1)
    {
        ui->comboBox->setCurrentIndex(index);
    }
}

void ComPortWidget::activatedEvent(int index)
{
    qDebug() << "ComPortWidget::activatedEvent " << mPortComList.at(index);

    DesktopApp::setPortCom(mPortComList.at(index));

}
