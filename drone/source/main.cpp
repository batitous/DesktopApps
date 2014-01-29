// Baptiste Burles, Kliplab, 2014

#include <QtWidgets/QApplication>
#include <QtCore/QDebug>
#include <QtCore/QFileInfo>

#include "../../ui/MainWindow.h"

int main(int argc, char *argv[])
{
    DesktopApp *  app = new DesktopApp(argc, argv);

    app->init("Kliplab", "Drone");

    qDebug() << "Hello World !";
    qDebug() << "getAppDirPath: " << Utils::getAppDirPath();

    QMainWindow * window = new MainWindow();

    window->show();

    return app->exec();
}

