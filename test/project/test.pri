
# Si jamais la compilation foire sous Mac OS X, il faut ajouter dans les paramètres du projet dans "Argument supplémentaires" : CONFIG+=x86_64

BABCODE_PATH = ../../../../babcode/babcode

QT += widgets

QMAKE += -j3

TEMPLATE = app

DESTDIR = ./

DEPENDPATH = .

INCLUDEPATH +=  . \
                ../include \
                ../source \
                $$BABCODE_PATH/include/
                

HEADERS += 

SOURCES += ../../source/main.cpp


mac {
    OBJECTS_DIR = ./buildOSX/
    MOC_DIR = ./buildOSX/
    UI_DIR = ./buildOSX/

    TARGET = Test

#    HEADERS += ../../../common/include/mac/mac.h

 #   SOURCES += ../../../common/source/utilsmacosx.cpp

  #  OBJECTIVE_SOURCES   += ../../../common/source/mac/mac.mm

    LIBS += $$BABCODE_PATH/project/macosx/Build/Products/Release/libbabcode-macosx.a \
                -framework AppKit -framework IOKit
}

unix:!mac {
    OBJECTS_DIR = ./buildUnix/
    MOC_DIR = ./buildUnix/
    UI_DIR = ./buildUnix/

    SOURCES += ../../../common/source/utilslinux.cpp

    TARGET = pobtools
}

win32 {
    OBJECTS_DIR = ./buildWin32/
    MOC_DIR = ./buildWin32/
    UI_DIR = ./buildWin32/

    TARGET = ./Debug/pobtools

    SOURCES             += ../../../common/source/utilswin32.cpp

#    RC_FILE *= version.rc

    LIBS += Advapi32.lib shell32.lib Ole32.lib Oleaut32.lib Rpcrt4.lib 
}
