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
#ifndef DESKTOP_APP_H
#define DESKTOP_APP_H

#include <QtWidgets/QApplication>
#include <QtCore/QTranslator>
#include <QtCore/QSettings>
#include <QtCore/QDebug>
#include <QtCore/QThread>

#include "recentfiles.h"
#include "utils.h"
#include "radiouart.h"
#include "fsm.h"
#include "queue.h"

class DesktopApp : public QApplication
{
    Q_OBJECT

public:
    DesktopApp(int &argc, char **argv, bool GUIenabled = true);
    ~DesktopApp();

    void init(const QString & companyName, const QString & applicatioName);

    // answer to the double-click on external file linked to your application
    bool event(QEvent *event);

    /* The object parameters must have :
     *  - a slot to start the object's code : void start();
     *  - a signal when finish Q_SIGNALS: void finished();
     */
    static QThread* launchObjectInThread(QObject* object);

    // restart the application and kill the actual
    static void restart();

    // retrieve the application's settings object
    static QSettings* settings();

    // get the recent files object
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
