# Baptiste Burles, Kliplab, 2014
#
# The symbol COMMON_PATH must be defined in the project that include this file.


INCLUDEPATH +=  $$COMMON_PATH/include \
                $$COMMON_PATH/source

HEADERS +=  $$COMMON_PATH/include/desktopapp.h \
            $$COMMON_PATH/include/desktopui.h \
            $$COMMON_PATH/include/utils.h \
            $$COMMON_PATH/include/recentfiles.h \
            $$COMMON_PATH/ui/dialog.h \
            $$COMMON_PATH/ui/comportwidget.h \
            $$COMMON_PATH/include/radiouart.h \
            $$COMMON_PATH/include/fsm.h \
            $$COMMON_PATH/include/queue.h

SOURCES +=  $$COMMON_PATH/source/desktopapp.cpp \
            $$COMMON_PATH/source/radiouart.cpp \
            $$COMMON_PATH/source/recentfiles.cpp \
            $$COMMON_PATH/ui/dialog.cpp \
            $$COMMON_PATH/ui/comportwidget.cpp \
            $$COMMON_PATH/source/fsm.cpp

FORMS +=    $$COMMON_PATH/ui/dialog.ui \
            $$COMMON_PATH/ui/comportwidget.ui

#use_firmware_nxp {
#
#FORMS +=    $$COMMON_PATH/ui/uploadwidget.ui \
#
#HEADERS += $$COMMON_PATH/libs/lpc2isp/lpc2isp-lib.h \
#             $$COMMON_PATH/ui/uploadwidget.h \
#            $$COMMON_PATH/include/firmware/firmwareupdate.h \
#            $$COMMON_PATH/include/firmware/nxpupdate.h

#SOURCES += $$COMMON_PATH/ui/uploadwidget.cpp \
#            $$COMMON_PATH/source/firmware/firmwareupdate.cpp \
#           $$COMMON_PATH/source/firmware/nxpupdate.cpp
#}

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

   LIBS += $$COMMON_PATH/libs/lpc2isp/lpc2isp.lib

# Visual studio library
#    LIBS += $$BABCODE_PATH/project/win32/libbabcode-win32.lib

# Mingw gcc library
    LIBS += -L$$BABCODE_PATH/project/win32/bin/Release -lbabcode -lws2_32 -liphlpapi

}

