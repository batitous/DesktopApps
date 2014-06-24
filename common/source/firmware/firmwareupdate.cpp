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

#include "../../include/firmware/firmwareUpdate.h"
#include "../include/desktopapp.h"

#include <QtCore/QStringList>
#include <QtCore/QDebug>

FirmwareUpdateInterface::FirmwareUpdateInterface()
{
    mStop		 = false;
    mIncrement	 = 5;
}

FirmwareUpdateInterface::~FirmwareUpdateInterface()
{
}

QString FirmwareUpdateInterface::error()
{
    return mError;
}

void FirmwareUpdateInterface::setFirmwareToUpload(QString &f)
{
    mFileToUpload = f;
}

void FirmwareUpdateInterface::run()
{
    int inc		= 0;
    int oldinc	= -1;
    int slow	= mIncrement;

    for( ; inc < 100 ; )
    {
        inc = this->getUploadProgress();

        if( inc == oldinc )
        {
            QThread::usleep(20000);
        }
        else
        {
            oldinc = inc;

            if(slow==0)
            {
                emit progress(inc);
                slow = mIncrement;
            }
            else
            {
                slow--;
            }
        }

        if( mStop==true)
        {
            return;
        }
    }

    emit progress(100);
}


void FirmwareUpdateInterface::update()
{
    QStringList comport;

    int size = Utils::getListOfPortCom(&comport);
    if( size == 0)
    {
        emit error(tr("Your robot is not connected on your computer !"));
    }
    else
    {
        mStop = false;
        this->start();

        bool result;
        QString currentPortCom = DesktopApp::portComFromSettings();

        qDebug()<< "FirmwareUpdateInterface::update try update on " << currentPortCom;

        if(currentPortCom.isEmpty()==true)
        {
            result = false;
        }
        else
        {
            result = this->upload(currentPortCom);
        }

        if(result==false)
        {
            for(int i=0;i<comport.size();i++)
            {
                if( comport.at(i) != currentPortCom)
                {
                    // thread exit when upload ended
                    mStop = false;
                    this->start();

                    qDebug() << "FirmwareUpdateInterface::update try update on " << comport.at(i);

                    result = this->upload(comport.at(i));
                    if(result==true)
                    {
                        QString tmp = comport.at(i);
                        DesktopApp::setPortCom(tmp);
                        break;
                    }
                }
            }
        }

//        qDebug() << "FirmwareUpdateInterface::update result = " << result;

        emit end(result);
    }
}
