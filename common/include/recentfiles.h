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
#ifndef DESKTOP_APP_RECENT_H
#define DESKTOP_APP_RECENT_H

#include <QtCore/QString>
#include <QtCore/QList>
#include <QtCore/QSettings>

typedef struct _recent_element_
{
    QString file;
    QString date;
    QString programName;
} RecentElement;


class RecentFiles
{
public:
    RecentFiles(QSettings * pSettings);
    ~RecentFiles();

    /* Save recent file to applications settings */
    void save();

    /* Add a file to the recent list */
    void add(QString file, QString programName);

    /* Get the list of files */
    QList<RecentElement *> * get();

    QString getFirstFile();

private:
    QSettings *             mSettings;
    QList<RecentElement *> * mList;
};

#endif
