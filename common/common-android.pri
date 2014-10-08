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
            $$COMMON_PATH/include/fsm.h \
            $$COMMON_PATH/include/queue.h

SOURCES +=  $$COMMON_PATH/source/desktopapp.cpp \
            $$COMMON_PATH/source/recentfiles.cpp \
            $$COMMON_PATH/ui/dialog.cpp \
            $$COMMON_PATH/ui/comportwidget.cpp \
            $$COMMON_PATH/source/fsm.cpp

FORMS +=    $$COMMON_PATH/ui/dialog.ui \
            $$COMMON_PATH/ui/comportwidget.ui


unix:!mac {
    SOURCES += $$COMMON_PATH/source/utilslinux.cpp
}

# android ndk dont support uart
#            $$COMMON_PATH/source/radiouart.cpp \
#            $$COMMON_PATH/include/radiouart.h \
