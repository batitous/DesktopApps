// Baptiste Burles, Kliplab, 2014

#include "../../include/firmware/nxpupdate.h"
#include "../../libs/lpc2isp/lpc2isp-lib.h"

#include <QtCore/QDebug>


NxpUpdateFirmware::NxpUpdateFirmware() : FirmwareUpdateInterface()
{
    mIncrement	= 5;
    mBaudrate	= 115200;

    mErrorMsg[0] = QObject::tr("Your robot doesn't answer, please reset it in programming mode !");
    mErrorMsg[1] = QObject::tr("Failed to read the firmware on your computer !");
    mErrorMsg[2] = QObject::tr("Can't communicate with your robot : restart it in programming mode. Error Code:");
    mErrorMsg[3] = QObject::tr("Can't open the USB port ");
}

NxpUpdateFirmware::~NxpUpdateFirmware()
{

}

bool NxpUpdateFirmware::upload(QString pPortCom)
{
    uint32_t result;

    result = (uint32_t)uploadToLpc21((char *)pPortCom.toLatin1().constData(),
                (char *)this->mFileToUpload.toLatin1().constData()
                );

    mStop = true;
    this->wait(ULONG_MAX);

    mError = "Success";

    if(result!=0)
    {
        switch(result)
        {
        case 1:
            mError = mErrorMsg[1];
            break;
        case 5:
            mError = mErrorMsg[3];
            break;
        case 8:
            mError = mErrorMsg[0];
            break;
        default:
            mError = mErrorMsg[2];
            mError += QString::number(result);
            break;
        }

        return false;
    }

    return true;
}

uint32_t NxpUpdateFirmware::getUploadProgress()
{
    return getUploadStatus();
}
