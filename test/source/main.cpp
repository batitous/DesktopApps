// Baptiste Burles, Kliplab, 2014
#include <QtWidgets/QApplication>
#include <QtCore/QDebug>
#include <QFileInfo>

#include "../../../common/include/desktopapp.h"
#include "../../../common/include/desktopui.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName(QString("Kliplab"));
    QCoreApplication::setApplicationName(QString("test"));

    DesktopApp *  app = new DesktopApp(argc, argv);

    qDebug() << "Hello World !";

    qDebug() << "getAppDirPath: " << Utils::getAppDirPath();
    qDebug() << "getTempDataPath: " << Utils::getTempDataPath();

    app->init();

    NxpUpdateFirmware * nxp = new NxpUpdateFirmware();

    UploadWidget * u = new UploadWidget();

    u->show();

    QString file = "/Users/baptiste/Desktop/Baptiste/projects/tests/POB/orbi/resources/firmwares/rs007_firmw_risbee.hex";
    nxp->setFirmwareToUpload(file);

    u->run(nxp);

    ComPortWidget * c = new ComPortWidget();
    c->refreshPortComList();
    c->show();

    return app->exec();
}

