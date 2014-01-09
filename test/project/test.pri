
# Si jamais la compilation foire sous Mac OS X, il faut ajouter dans les paramètres du projet dans "Argument supplémentaires" : CONFIG+=x86_64

BABCODE_PATH = ../../../../babcode/babcode

COMMON_PATH = ../../../common
include(../../common/common.pri)

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
}

unix:!mac {
    OBJECTS_DIR = ./buildUnix/
    MOC_DIR = ./buildUnix/
    UI_DIR = ./buildUnix/

    TARGET = test
}

win32 {
    OBJECTS_DIR = ./buildWin32/
    MOC_DIR = ./buildWin32/
    UI_DIR = ./buildWin32/

    TARGET = ./Debug/test

#    RC_FILE *= version.rc

    LIBS += Advapi32.lib shell32.lib Ole32.lib Oleaut32.lib Rpcrt4.lib 
}
