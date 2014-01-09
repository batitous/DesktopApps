// Baptiste Burles, Kliplab, 2014
#ifndef DESKTOP_APP_NXP_UPDATE_H
#define DESKTOP_APP_NXP_UPDATE_H

#include "firmwareupdate.h"

class NxpUpdateFirmware : public FirmwareUpdateInterface
{
public:
    NxpUpdateFirmware();
    ~NxpUpdateFirmware();

    bool upload(QString pPortCom);
    UInt32 getUploadProgress();

private:
    UInt32		mBaudrate;
    QString		mErrorMsg[4];

};

#endif
