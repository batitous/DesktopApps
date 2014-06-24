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
#ifndef UPLOADWIDGET_H
#define UPLOADWIDGET_H

#include <QWidget>

#include "../include/firmware/firmwareupdate.h"
#include "../include/firmware/nxpupdate.h"

namespace Ui {
class UploadWidget;
}

class UploadWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UploadWidget(QWidget *parent = 0);
    ~UploadWidget();

    void init();
    bool run(FirmwareUpdateInterface * f);

public slots:
    void progressEvent(int inc);
    void errorEvent(QString str);
    void endEvent(bool ok);
    void launchUpdateEvent();

private:
    Ui::UploadWidget *          ui;
    FirmwareUpdateInterface *   mFirmware;
};

#endif // UPLOADWIDGET_H
