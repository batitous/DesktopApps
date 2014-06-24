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
