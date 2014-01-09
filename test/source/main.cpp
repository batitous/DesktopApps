
#include <QtWidgets/QApplication>
#include <QtCore/QDebug>

#include "../../../common/include/desktopapp.h"

#include "../../../common/ui/uploadwidget.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName(QString("Kliplab"));
    QCoreApplication::setApplicationName(QString("test"));

    DesktopApp *  app = new DesktopApp(argc, argv);

    qDebug() << "Hello World !";

    QStringList ports;
    int n = Utils::getListOfPortCom(&ports);
    qDebug() << "USB Port: " << ports.at(0);

    qDebug() << "getAppDirPath: " << Utils::getAppDirPath();
    qDebug() << "getCommonUserDataPath: " << Utils::getCommonUserDataPath();
    qDebug() << "getTempDataPath: " << Utils::getTempDataPath();

    app->init();

    NxpUpdateFirmware * nxp = new NxpUpdateFirmware();

    UploadWidget * u = new UploadWidget();

    u->show();

    QString file = "/Users/baptiste/Desktop/Baptiste/projects/tests/POB/orbi/resources/firmwares/rs007_firmw_risbee.hex";
    nxp->setFirmwareToUpload(file);

    u->run(nxp);

    return app->exec();
}

