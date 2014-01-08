
#ifndef DESKTOP_APP_H
#define DESKTOP_APP_H

#include <QtWidgets/QApplication>
#include <QtCore/QTranslator>
#include <QtCore/QSettings>
#include <QtCore/QDebug>

#include "recentfiles.h"
#include "utils.h"

class DesktopApp : public QApplication
{
    Q_OBJECT

public:
    DesktopApp(int &argc, char **argv, bool GUIenabled = true);
    ~DesktopApp();

    void init();

    bool event(QEvent *event);

    static QSettings* settings();
    static RecentFiles* recentfiles();

    static QString lang();
    static void setLang(QString & lang);

signals:
    void openFile(QString filename);

private:
    static QSettings *		mSettings;
    static RecentFiles *    mRecentFiles;

    QTranslator *           mTranslator;


    void loadLang(QString name);
};


#endif
