TARGET   = IsomerAPI
TEMPLATE = app
QT       += widgets sql
CONFIG   += c++17 console
CONFIG   -= app_bundle


win32-g++ {
DESTDIR = C:/IsomerAPI/_install
}
win32-msvc {
DESTDIR = c:/IsomerAPI/_install_MSVC
}

win32:VERSION = 1.3.10.0 # major.minor.patch.build
else:VERSION  = 1.3.10   # major.minor.patch
VERSION_STR = $$section(VERSION, ., 0, 2)

win32 {
    QMAKE_TARGET_COPYRIGHT = "LISE group at FRIB/MSU"
    QMAKE_TARGET_COMPANY   = "LISE group at FRIB/MSU"
}


# important to eliminate some LISEcute functions in IsomerAPI project
DEFINES += IsomerAPI_case

# Sources
SOURCES += \
    L_Element/o_Element.cpp \
    w_Isomer/d_Columns.cpp \
    w_Isomer/iso_main.cpp \
    w_Isomer/w_IsomerAPI.cpp \
    w_Isomer/w_levelScheme.cpp \
    w_Isomer/w_graphicsView.cpp \
    w_Isomer/w_about.cpp \
    w_Isomer/d_Download.cpp \
    w_Stuff/w_Label_clickable.cpp \
    w_Stuff/win_utilCalc.cpp \
    w_Stuff/win_utilPlot.cpp \
    w_Stuff/win_utilString.cpp

# Headers
HEADERS += \
    L_Element/o_Element.h \
    L_Init/Constant.h \
    L_Init/L_ValueErr.h \
    L_Init/declare_IsomerAPI.h \
    L_Init/myextern_IsomerAPI.h \
    L_Init/mytypes_IsomerAPI.h \
    w_Isomer/L_element.h \
    w_Isomer/L_isomerAPI_version.h \
    w_Isomer/d_Columns.h \
    w_Isomer/w_IsomerAPI.h \
    w_Isomer/w_levelScheme.h \
    w_Isomer/w_graphicsView.h \
    w_Isomer/L_vectorStruct.h \
    w_Isomer/w_about.h \
    w_Isomer/d_Download.h \
    w_Stuff/liseStrcpyOS.h \
    w_Stuff/o_error_function.h \
    w_Stuff/w_Label_clickable.h

# UI forms
FORMS += \
    w_Isomer/d_Columns.ui \
    w_Isomer/w_IsomerAPI.ui \
    w_Isomer/w_levelScheme.ui \
    w_Isomer/w_about.ui \
    w_Isomer/d_Download.ui

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
    _install/lisecfg/IsomerDB_Split.sqlite \
    _install/lisecfg/Isomer_DB_WIDGET.sqlite \
    _install/lisecfg/nndc_DB.sqlite \
    mainstyle.qss
    mainstyle_light.qss

RESOURCES += \
    w_Isomer/isomapi_resources.qrc

DISTFILES += \
       w_Isomer/Icons/IsomerAPI_icon.ico

RC_ICONS +=  \
       w_Isomer/Icons/IsomerAPI_icon.ico



