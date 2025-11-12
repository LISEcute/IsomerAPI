TARGET   = IsomerAPI
TEMPLATE = app
QT       += widgets sql
CONFIG   += c++17 console
CONFIG   -= app_bundle


win32-g++ {
DESTDIR = c:/IsomerAPI/_install
}
win32-msvc {
DESTDIR = c:/IsomerAPI/_install_MSVC
}


# Sources
SOURCES += \
    main.cpp \
    w_Isomer/w_IsomerAPI.cpp \
    w_Isomer/w_levelScheme.cpp \
    w_Isomer/w_graphicsView.cpp \
    w_Stuff/win_utilPlot.cpp \
    w_Stuff/win_utilString.cpp

# Headers
HEADERS += \
    w_Isomer/w_IsomerAPI.h \
    w_Isomer/w_levelScheme.h \
    w_Isomer/w_graphicsView.h \
    w_Isomer/L_vectorStruct.h \
    w_Isomer/L_isomerAPIversion.h \
    w_Stuff/liseStrcpyOS.h

# UI forms
FORMS += \
    w_Isomer/w_IsomerAPI.ui \
    w_Isomer/w_levelScheme.ui

# Include path
INCLUDEPATH += $$PWD

# Database file (tracked for IDE, packaging, etc.)
# DISTFILES += database_store/Isomer_DB_WIDGET.sqlite

# Ensure database_store/ exists in build dir, then copy DB after build
# QMAKE_POST_LINK += $$QMAKE_MKDIR \"$$OUT_PWD/database_store\"
# QMAKE_POST_LINK += $$QMAKE_COPY \"$$PWD/database_store/Isomer_DB_WIDGET.sqlite\" \
#                                  \"$$OUT_PWD/database_store/Isomer_DB_WIDGET.sqlite\"

# Handle Qt version differences
greaterThan(QT_MAJOR_VERSION, 5) {
    message("Building with Qt6")
    CONFIG += c++17
} else {
    message("Building with Qt5")
    CONFIG += c++17
}

DISTFILES += \
    _install/lisecfg/Isomer_DB_WIDGET.sqlite \
    mainstyle.qss
