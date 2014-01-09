# Baptiste Burles, Kliplab, 2014
#
# The symbol COMMON_PATH must be defined in the project that include this file.


INCLUDEPATH +=  $$COMMON_PATH/include \
                $$COMMON_PATH/source

HEADERS +=  $$COMMON_PATH/libs/lpc2isp/lpc2isp-lib.h \
            $$COMMON_PATH/include/desktopapp.h \
            $$COMMON_PATH/include/firmware/firmwareupdate.h \
            $$COMMON_PATH/include/firmware/nxpupdate.h \
            $$COMMON_PATH/include/utils.h \
            $$COMMON_PATH/include/recentfiles.h \
            $$COMMON_PATH/ui/uploadwidget.h \
            $$COMMON_PATH/ui/dialog.h

SOURCES +=  $$COMMON_PATH/source/desktopapp.cpp \
            $$COMMON_PATH/source/firmware/firmwareupdate.cpp \
            $$COMMON_PATH/source/firmware/nxpupdate.cpp \
            $$COMMON_PATH/source/recentfiles.cpp \
            $$COMMON_PATH/ui/uploadwidget.cpp \
            $$COMMON_PATH/ui/dialog.cpp

FORMS +=    $$COMMON_PATH/ui/uploadwidget.ui \
            $$COMMON_PATH/ui/dialog.ui

mac {
    SOURCES += $$COMMON_PATH/source/utilsmacosx.cpp

    LIBS += $$COMMON_PATH/libs/lpc2isp/liblpc2isp-macosx.a

    LIBS += $$BABCODE_PATH/project/macosx/Build/Products/Release/libbabcode-macosx.a

    LIBS += -framework AppKit -framework IOKit
}

unix:!mac {
    SOURCES += $$COMMON_PATH/source/utilslinux.cpp
}

win32 {
    SOURCES += $$COMMON_PATH/source/utilswin32.cpp
}

