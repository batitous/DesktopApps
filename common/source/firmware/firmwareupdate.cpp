// Baptiste Burles, Kliplab, 2014

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
