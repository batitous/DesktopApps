// Baptiste Burles, Kliplab, 2014
#include <QtWidgets/QApplication>
#include <QtCore/QDebug>
#include <QFileInfo>

#include "../../../common/include/desktopapp.h"
#include "../../../common/include/desktopui.h"

int main(int argc, char *argv[])
{
    DesktopApp *  app = new DesktopApp(argc, argv);

    qDebug() << "Hello World !";
    qDebug() << "getAppDirPath: " << Utils::getAppDirPath();

    app->init("Kliplab", "test");

    QWidget * w = new QWidget();
    ComPortWidget * c = new ComPortWidget(w);
    c->refreshPortComList();
    c->move(0,1);

    UploadWidget * u = new UploadWidget(w);
    u->move(0,100);

    QString file = "/Users/baptiste/Desktop/Baptiste/projects/tests/POB/orbi/resources/firmwares/rs007_firmw_risbee.hex";

    NxpUpdateFirmware * nxp = new NxpUpdateFirmware();
    nxp->setFirmwareToUpload(file);

    u->run(nxp);

    w->show();

    return app->exec();
}

