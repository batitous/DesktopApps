
#include <babcode.h>

#include "../include/utils.h"

#include <QtCore/QDebug>
#include <QtCore/QCoreApplication>
#include <QtCore/QSysInfo>

int Utils::getListOfPortCom(QStringList *portCombo)
{
    // Read windows registry:
    QSettings settings("HKEY_LOCAL_MACHINE\\hardware\\devicemap\\serialcomm",QSettings::NativeFormat);

    // Get keys list:
    QStringList list = settings.childKeys();

    portCombo->clear();

    // Add serial port to the combo box:
    for(int i = list.size()-1; i >= 0; i--)
    {
        list[i].replace(QString("/"),QString("\\"));

        QString str = Utils::getPortCom("hardware\\devicemap\\serialcomm",list[i]);

        portCombo->append(str);
    }

    return list.size();
}

#include <windows.h>


QString Utils::getPortCom(QString subkey, QString key)
{
    QString value = "";

    HKEY hKey;
    LPTSTR lpSubKey, pKey;
//	PTSTR  lpSubKey[256], pKey[256];
    LONG lResult;
    UInt8 data[256];
    DWORD size;
    int i,j;

    //warning all string are in Unicode (16 bits)!

    lpSubKey = (LPTSTR)malloc( 2*subkey.length()+2 );

    for(i=0;i<subkey.length();i++)
    {
        lpSubKey[i]=subkey[i].toLatin1();
    }
    lpSubKey[i]=0;

    lResult = RegOpenKeyEx (HKEY_LOCAL_MACHINE, lpSubKey, 0, KEY_READ, &hKey);

    if (lResult != ERROR_SUCCESS)
    {
//		LogAdd(1,"UploadSelectUi::getPortCom failed to open registry");
        free(lpSubKey);
        return value;
    }

    pKey = (LPTSTR)malloc( 2*key.length()+2 );
    for( i=0;i<key.length();i++)
    {
        pKey[i]=key[i].toLatin1();
    }
    pKey[i]=0;

    size = 256;
    lResult = RegQueryValueEx(hKey, pKey,0,0, data, &size);
    if (lResult != ERROR_SUCCESS)
    {
//		LogAdd(1,"UploadSelectUi::getPortCom failed to read registry");
        free(lpSubKey);
        free(pKey);
        return value;
    }

//	printf("Size=%d\n", size);

    for( i=0, j=0;j<size-2;i++,j=j+2)
    {
        value[i]=data[j];
    }

    RegCloseKey (hKey);

    free(lpSubKey);
    free(pKey);

    return value;
}

#include <shlobj.h>

QString Utils::getAppDirPath()
{
    return QCoreApplication::applicationDirPath();
}

QString Utils::getCommonUserDataPath()
{
    return getSpecialRepertory(CSIDL_COMMON_APPDATA);
}

QString Utils::getUserDataPath()
{
    return getSpecialRepertory(CSIDL_APPDATA/*CSIDL_LOCAL_APPDATA*/);
}

QString Utils::getTempDataPath()
{
    return Utils::getUserData();
}

QString Utils::getSpecialRepertory(int rep)
{
   TCHAR szPath[MAX_PATH];
   QString value = "";
   UInt32 i;

   if ( SUCCEEDED( SHGetFolderPath( NULL, rep,NULL, SHGFP_TYPE_CURRENT, szPath ) ) )
   {

        for( i=0; szPath[i] != 0 ; i++)
        {
            value[i] = szPath[i];
        }
   }

   //TODO add application name
   qDebug() << "Utils::getSpecialRepertory TODO " << value;

   return value;
}
