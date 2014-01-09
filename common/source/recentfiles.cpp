// Baptiste Burles, Kliplab, 2014

#include "../include/recentfiles.h"

#include <QtCore/QStringList>
#include <QtCore/QDate>
#include <QtCore/QDebug>


RecentFiles::RecentFiles(QSettings * pSettings)
{
    mSettings = pSettings;
    mList = new QList<RecentElement *>;

    // load list of recent files from the settings
    QString key = "RECENT";
    QString tmp0,tmp1;
    RecentElement * elem;

    for(int i=0;i<5;i++)
    {
        tmp1 = key + QString::number(i);
        tmp0 = mSettings->value(tmp1).toString();

        if(tmp0.isEmpty()==false)
        {
            QStringList l = tmp0.split("|");
            elem = new RecentElement;
            elem->file = l.at(0);
            elem->date = l.at(1);
            elem->programName = l.at(2);
            mList->append(elem);
        }
    }
}

RecentFiles::~RecentFiles()
{
}

void RecentFiles::save()
{
    QString key = "RECENT";
    QString tmp0,tmp1;
    for(int i=0;i<mList->count();i++)
    {
        tmp1 = key + QString::number(i);
        tmp0 = mList->at(i)->file + "|"+ mList->at(i)->date+"|"+mList->at(i)->programName;

        mSettings->setValue(tmp1, QVariant(tmp0) );
    }
}

void RecentFiles::add(QString file, QString programName)
{
    int i;
    QString date ;
    RecentElement * elem;

    date = QDate::currentDate().toString("dd/MM/yyyy");

    elem = new RecentElement;
    elem->file = file;
    elem->date = date;
    elem->programName = programName;

    for(i=0;i< mList->count();i++)
    {
        if( file == mList->at(i)->file)
        {
            mList->removeAt(i);
            mList->insert(0,elem);
            return;
        }
    }

    mList->insert(0,elem);

    if( mList->count()>5)
    {
        mList->removeLast();
    }
}


QList<RecentElement *> * RecentFiles::get()
{
    // if list empty, grab the documents repertory instead ?
//    QString tmp = QDesktopServices::storageLocation(QDesktopServices::DocumentsLocation) + "/temp.tmp";

    return mList;
}
