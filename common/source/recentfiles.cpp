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

#include "../include/recentfiles.h"

#include <QtCore/QStringList>
#include <QtCore/QDate>
#include <QtCore/QDebug>
#include <QtGui/QDesktopServices>


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
    return mList;
}

QString RecentFiles::getFirstFile()
{
    if(mList->count()==0)
    {
        return QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation).at(0)+"/temp.tmp";
    }

    return mList->at(0)->file;
}
