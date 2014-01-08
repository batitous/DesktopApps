
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    int result = -1;

    QApplication a(argc, argv);

    result =  a.exec();

    QApplication::exit(result);

    return result;
}

