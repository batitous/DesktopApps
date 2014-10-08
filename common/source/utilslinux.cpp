/* The MIT License (MIT)

 Copyright (c) 2014 Baptiste Burles, Kliplab

 Permission is hereby granted, free of charge, to any person obtaining a copy of
 this software and associated documentation files (the "Software"), to deal in
 the Software without restriction, including without limitation the rights to
 use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 the Software, and to permit persons to whom the Software is furnished to do so,
 subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

 */
#include <QtCore/QCoreApplication>

#ifdef Q_OS_UNIX

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


QString Utils::getPortCom(QString subkey, QString key)
{
    Q_UNUSED(subkey);
    Q_UNUSED(key);

    QString value = "";

    return value;
}

QString Utils::getAppDirPath()
{
    return QCoreApplication::applicationDirPath()+"/";
}

QString Utils::getUserDataPath()
{
    return QStandardPaths::standardLocations(QStandardPaths::DataLocation).at(0);
}

QString Utils::getTempDataPath()
{
    return QStandardPaths::standardLocations(QStandardPaths::TempLocation).at(0)+"/Kliplab";
}

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
         pch=strstr(read->d_name,"tty");
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


#endif
