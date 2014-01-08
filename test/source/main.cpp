
#include <QtWidgets/QApplication>
#include <QtCore/QDebug>

#include "../../../common/include/desktopapp.h"

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

    return app->exec();
}

