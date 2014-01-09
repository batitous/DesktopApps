// Baptiste Burles, Kliplab, 2014
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
