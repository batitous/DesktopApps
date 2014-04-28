// Baptiste Burles, Kliplab, 2014
#ifndef DESKTOP_APP_FIRMWARE_UPDATE_H
#define DESKTOP_APP_FIRMWARE_UPDATE_H

#include <babcode.h>

#include <QtCore/QString>
#include <QtCore/QThread>

class FirmwareUpdateInterface : public QThread
{
Q_OBJECT

signals:

    void progress(int pIncrement);

    void error(QString str);

    void end(bool ok);

public:
    FirmwareUpdateInterface();
    ~FirmwareUpdateInterface();

    void update();

    QString error();

    void setFirmwareToUpload(QString & pHexFile);

protected:
    virtual bool upload(QString pPortCom) = 0;
    virtual uint32_t getUploadProgress() = 0;

    QString			mFileToUpload;	/**< file to upload into memory */
    QString			mError;			/**< error message */
    bool			mStop;			/**< stop upload */
    uint32_t        mIncrement;

private:
    void run();
};


#endif
