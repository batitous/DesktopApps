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
