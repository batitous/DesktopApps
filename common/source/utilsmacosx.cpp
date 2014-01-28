// Baptiste Burles, Kliplab, 2014

#include <QtCore/QCoreApplication>

#ifdef Q_OS_DARWIN

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

#include <babcode.h>

#include "../include/utils.h"

#include <QtCore/QDebug>
#include <QtCore/QStringList>

#include <QtCore/QProcess>
#include <QtGui/QDesktopServices>


int Utils::getListOfPortCom(QStringList *portCombo)
{
         struct dirent *read;
         DIR *rep;
         int list;
         char *dirname = new char(100);

         list=false ;
         dirname = (char*)"/dev/\0";

         rep = opendir(dirname);
         char * pch;
         QStringList listPorts;
         QString str = "/dev/";
         while((read = readdir(rep)))
         {
             pch=strstr(read->d_name,"cu");
             if(pch!=NULL)
             {
                 pch=strstr(read->d_name,"Bluetooth");
                 if(pch==NULL)
                 {
                    str = "/dev/";
                    str += read->d_name;
                    listPorts<<str;
                }
             }
         }
         closedir(rep);


         if(listPorts.size() == 0)
         {
             //"No valid serial device found in /dev, sorry !\nYou should have at least one of these :\n/dev/ttyS*\n/dev/tts/*\n/dev/ttyUSB*\n/dev/usb/tts/*\n"
             return 0;
         }
         else
         {
             portCombo->clear();

             //Insert serial port ont the combo box
             for(int i=0; i < listPorts.size() ; i++)
             {
                 portCombo->append(listPorts[i]);

             }//..for
         }//..else

         return listPorts.size();
}

QString Utils::getPortCom(QString subkey, QString key)
{
    Q_UNUSED(subkey);
    Q_UNUSED(key);

    QString value = "";

    return value;
}

QString Utils::getAppDirPath()
{
    return QCoreApplication::applicationDirPath()+"/../Resources";
}

QString Utils::getUserDataPath()
{
    return QStandardPaths::standardLocations(QStandardPaths::DataLocation).at(0);
}

QString Utils::getTempDataPath()
{
    return QStandardPaths::standardLocations(QStandardPaths::TempLocation).at(0)+"/Kliplab";
}

#endif
