// Baptiste Burles, Kliplab, 2014
#ifndef DESKTOP_APP_H
#define DESKTOP_APP_H

#include <QtWidgets/QApplication>
#include <QtCore/QTranslator>
#include <QtCore/QSettings>
#include <QtCore/QDebug>

#include "recentfiles.h"
#include "utils.h"
#include "radiouart.h"

class DesktopApp : public QApplication
{
    Q_OBJECT

public:
    DesktopApp(int &argc, char **argv, bool GUIenabled = true);
    ~DesktopApp();

    void init(const QString & companyName, const QString & applicatioName);

    bool event(QEvent *event);

    static QSettings* settings();
    static RecentFiles* recentfiles();

    static QString langFromSettings();
    static void setLang(const QString & lang);

    static QString portComFromSettings();
    static void setPortCom(const QString & portcom);

signals:
    void openFile(QString filename);

private:
    static QSettings *		mSettings;
    static RecentFiles *    mRecentFiles;

    QTranslator *           mTranslator;


    void loadLang(QString name);
};


#endif
