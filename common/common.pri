# The symbol COMMON_PATH must be defined in the project that include this file.


INCLUDEPATH +=  $$COMMON_PATH/include \
                $$COMMON_PATH/source

HEADERS +=  $$COMMON_PATH/include/desktopapp.h \
            $$COMMON_PATH/include/utils.h \
            $$COMMON_PATH/include/recentfiles.h \

SOURCES +=  $$COMMON_PATH/source/desktopapp.cpp \
            $$COMMON_PATH/source/recentfiles.cpp


mac {
    SOURCES += $$COMMON_PATH/source/utilsmacosx.cpp
}

unix:!mac {
    SOURCES += $$COMMON_PATH/source/utilslinux.cpp
}

win32 {
    SOURCES += $$COMMON_PATH/source/utilswin32.cpp
}
