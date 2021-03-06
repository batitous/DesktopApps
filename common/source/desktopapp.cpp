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

#include "../include/desktopapp.h"

#include <QtCore/QDir>
#include <QtCore/QProcess>
#include <QtGui/QFileOpenEvent>


QSettings* DesktopApp::mSettings = 0;
RecentFiles* DesktopApp::mRecentFiles = 0;

static FILE* desktopAppOutputDebug=NULL;


QSettings* DesktopApp::settings()
{
    return mSettings;
}

RecentFiles* DesktopApp::recentfiles()
{
    return mRecentFiles;
}

QString DesktopApp::langFromSettings()
{
    return mSettings->value("LANG").toString();;
}

void DesktopApp::setLang(const QString & lang)
{
    mSettings->setValue("LANG", QVariant(lang));
}

QString DesktopApp::portComFromSettings()
{
    return mSettings->value("COM").toString();
}

void DesktopApp::setPortCom(const QString & portcom)
{
    mSettings->setValue("COM", QVariant(portcom));
}

void desktopAppMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
 {
     if(desktopAppOutputDebug==NULL)
         return;

     QByteArray localMsg = msg.toLocal8Bit();
     switch (type)
     {
     case QtDebugMsg:
         fprintf(desktopAppOutputDebug, "%s\n", localMsg.constData());
         break;
     case QtWarningMsg:
         fprintf(desktopAppOutputDebug, "Warning: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
         break;
     case QtCriticalMsg:
         fprintf(desktopAppOutputDebug, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
         break;
     case QtFatalMsg:
         fprintf(desktopAppOutputDebug, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
     }

     fflush(desktopAppOutputDebug);
 }

DesktopApp::DesktopApp(int &argc, char **argv, bool GUIenabled) : QApplication(argc, argv, GUIenabled)
{
}

DesktopApp::~DesktopApp()
{

}

void DesktopApp::init(const QString & companyName, const QString & applicationName)
{
    // Set organization/application name
    QCoreApplication::setOrganizationName(companyName);
    QCoreApplication::setApplicationName(applicationName);

    QString name = QCoreApplication::applicationName();

    // Init settings
    mSettings = new QSettings( QSettings::NativeFormat,
                                        QSettings::UserScope,
                                        QCoreApplication::organizationName(),
                                        name);

    // Get recent files
    mRecentFiles = new RecentFiles(mSettings);

    // Add Qt plugins repertory
    QString plugins = Utils::getAppDirPath() + "/resources/plugins";

    QCoreApplication::addLibraryPath(plugins);

    // Create application repertory
    QString path = Utils::getUserDataPath();

    QDir dir(path);
    if( dir.exists() == false)
    {
        dir.mkpath(path);
    }

    // If we are on a release application then all the console output go into a file
#ifdef QT_NO_DEBUG
    QString log = path+"/"+name+".log";
    desktopAppOutputDebug = fopen((char *)log.toLatin1().constData(),"w+");
    qInstallMessageHandler(desktopAppMessageOutput);
#endif

    QString babcodelog = path +"/babcode.log";
    Log::global()->start(babcodelog.toLatin1().constData(), true);

    qDebug() << "DesktopApp::init local resources:" << path;

    // Load the specific lang
    loadLang(name);
}

void DesktopApp::loadLang(QString name)
{
    QString lang = DesktopApp::langFromSettings();
    QString locale = lang;

    if(lang.isEmpty()==true)
    {
        QString locale1 = QLocale::system().name();

        locale = locale1.section('_', 0, 0);
    }

    mTranslator = new QTranslator();

    qDebug() << "DesktopApp::loadLang detected: " << QLocale::system().name() << " lang selected: " << locale ;

    if( mTranslator->load(Utils::getAppDirPath()+QString("/resources/lang/" + name + "_") + locale) == true)
    {
        this->installTranslator(mTranslator);
    }
    else
    {
        locale = "en";
    }

    if(lang.isEmpty()==true)
    {
        DesktopApp::setLang(locale);
    }
}

bool DesktopApp::event(QEvent *event)
{
    // get event when double click on file
    if (event->type() == QEvent::FileOpen)
    {
        QFileOpenEvent *foe = static_cast<QFileOpenEvent*>(event);
        emit openFile(foe->file());
        return true;
    }

    return QApplication::event(event);
}


QThread* DesktopApp::launchObjectInThread(QObject* object)
{
    QThread* thread = new QThread;

    object->moveToThread(thread);

    connect(thread, SIGNAL(started()), object, SLOT(start()));
    connect(object, SIGNAL(finished()), thread, SLOT(quit()));
    connect(object, SIGNAL(finished()), object, SLOT(deleteLater()));
    connect(object, SIGNAL(finished()), thread, SLOT(deleteLater()));

    thread->start();

    return thread;
}

void DesktopApp::restart()
{
    QString app = QApplication::applicationFilePath();
    QStringList arguments = QApplication::arguments();
    QString wd = QDir::currentPath();

    QProcess::startDetached(app, arguments, wd);
    QApplication::exit();
}
