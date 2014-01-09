#include "uploadwidget.h"
#include "ui_uploadwidget.h"

#include <QtCore/QDebug>
#include <QtCore/QTimer>

#include "dialog.h"

UploadWidget::UploadWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UploadWidget)
{
    ui->setupUi(this);

    init();

    mFirmware = 0;

}

UploadWidget::~UploadWidget()
{
    delete ui;
}

void UploadWidget::init()
{
    ui->label->setText(tr("Wait CPU reset..."));

    ui->progressBar->setValue(0);
    ui->progressBar->setMaximum(100);

    //ui->progressBar->hide();
}

bool UploadWidget::run(FirmwareUpdateInterface * f)
{
    if(mFirmware!=0)
    {
        disconnect(mFirmware,SIGNAL(updateProgress(int)),0,0);
        disconnect(mFirmware,SIGNAL(error(QString)), 0,0);
        disconnect(mFirmware,SIGNAL(end(bool)),0,0);
    }

    mFirmware = f;

    if (mFirmware->isRunning()==true)
    {
        qDebug() << "UploadWidget::run error thread is already running !";
        return false;
    }

    connect(mFirmware, SIGNAL(progress(int)), this, SLOT(progressEvent(int)) );
    connect(mFirmware, SIGNAL(error(QString)), this, SLOT(errorEvent(QString)) );
    connect(mFirmware, SIGNAL(end(bool)), this, SLOT(endEvent(bool)) );

    QTimer::singleShot(0, this, SLOT(launchUpdateEvent()));

    return true;
}

void UploadWidget::launchUpdateEvent()
{
    mFirmware->update();
}

void UploadWidget::progressEvent(int inc)
{
    ui->progressBar->setValue(inc);
}

void UploadWidget::errorEvent(QString str)
{
    qDebug() << "UploadWidget::errorEvent " << str;
}

void UploadWidget::endEvent(bool ok)
{
    qDebug() << "UploadWidget::endEvent " << ok << " error " << mFirmware->error();

    Dialog * dialog = new Dialog(this);

    dialog->setButton(Dialog::Left, Dialog::Accept, "Oki", false);
    dialog->setButton(Dialog::Right, Dialog::Reject, "Cancel", false);

    int result = dialog->show(Dialog::Error, tr("Ypiiii"), QString("lsdkfjsldkfjsldkfjsldkfjlsjdkfj un grand message sur plusieurs lignes ????"));

    qDebug() << " RESULT CLICK = " << result;

}
