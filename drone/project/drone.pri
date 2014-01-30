
# Si jamais la compilation foire sous Mac OS X, il faut ajouter dans les paramètres du projet dans "Argument supplémentaires" : CONFIG+=x86_64

BABCODE_PATH = ../../../../babcode/babcode

COMMON_PATH = ../../../common
include(../../common/common.pri)

QT += widgets opengl concurrent

QMAKE += -j3
TEMPLATE = app
DESTDIR = ./
DEPENDPATH = .

INCLUDEPATH +=  . \
                ../include \
                ../source \
                ../ui \
                $$BABCODE_PATH/include
                

HEADERS +=  ../../ui/MainWindow.h \
    ../../include/drone.h \
    ../../include/droneprotocol.h \
    ../../include/gl/model.h \
    ../../include/gl/openglscene.h \
    ../../include/gl/point3d.h \

SOURCES +=  ../../source/main.cpp \
    ../../ui/MainWindow.cpp \
    ../../source/drone.cpp \
    ../../source/gl/model.cpp \
    ../../source/gl/openglscene.cpp \

FORMS   += ../../ui/MainWindow.ui


mac {
    OBJECTS_DIR = ./buildOSX/
    MOC_DIR = ./buildOSX/
    UI_DIR = ./buildOSX/

    TARGET = Drone
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

RESOURCES += \
    ../../resources/resources.qrc
