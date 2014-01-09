// Baptiste Burles, Kliplab, 2014

#include "../include/desktopapp.h"

#include <QtCore/QDir>
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

void DesktopApp::setLang(QString & lang)
{
    mSettings->setValue("LANG", QVariant(lang));
}

QString DesktopApp::portComFromSettings()
{
    return mSettings->value("COM").toString();
}

void DesktopApp::setPortCom(QString & portcom)
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

void DesktopApp::init()
{
    QString name = QCoreApplication::applicationName();

    // Init settings
    mSettings = new QSettings( QSettings::NativeFormat,
                                        QSettings::UserScope,
                                        QCoreApplication::organizationName(),
                                        name);

    // Get recent files
    mRecentFiles = new RecentFiles(mSettings);

    /* Add Qt plugins repertory */
    QString plugins = Utils::getAppDirPath() + "/resources/plugins";

    QCoreApplication::addLibraryPath(plugins);

    // Create application repertory */
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
