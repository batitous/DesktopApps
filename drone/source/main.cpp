// Baptiste Burles, Kliplab, 2014

#include <QtWidgets/QApplication>
#include <QtCore/QDebug>
#include <QFileInfo>

#include "../../ui/MainWindow.h"

int main(int argc, char *argv[])
{
    DesktopApp *  app = new DesktopApp(argc, argv);

    qDebug() << "Hello World !";
    qDebug() << "getAppDirPath: " << Utils::getAppDirPath();

    app->init("Kliplab", "Drone");

    QMainWindow * window = new MainWindow();

    window->show();

    return app->exec();
}

