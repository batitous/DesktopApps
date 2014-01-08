
#ifndef DESKTOP_APP_UTILS_H
#define DESKTOP_APP_UTILS_H

#include <QtCore/QStringList>

class Utils
{
public:
    static int getListOfPortCom(QStringList *portList);

    static QString getCommonUserDataPath();
    static QString getUserDataPath();
    static QString getTempDataPath();
    static QString getAppDirPath();

private:
    static QString getSpecialRepertory(int rep);
    static QString getPortCom(QString subkey, QString key);
};

#endif
