/* The MIT License (MIT)
 
 Copyright (c) 2014 Baptiste Burles, Kliplab
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of
 this software and associated documentation files (the "Software"), to deal in
 the Software without restriction, including without limitation the rights to
 use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 the Software, and to permit persons to whom the Software is furnished to do so,
 subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 
 */
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
    dialog->setButton(Dialog::Right, Dialog::Reject, "Cancel", true);

    int result = dialog->show(Dialog::Error, tr("Ypiiii"), QString("lsdkfjsldkfjsldkfjsldkfjlsjdkfj un grand message sur plusieurs lignes ????"));

    qDebug() << " RESULT CLICK = " << result;

}
