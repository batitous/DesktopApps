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
