TARGET   = IsomerAPI
TEMPLATE = app
QT       += widgets sql
CONFIG   += c++17 console
CONFIG   -= app_bundle


win32-g++ {
DESTDIR = $$PWD/_install
}
win32-msvc {
DESTDIR = $$PWD/_install_MSVC
}

win32:VERSION = 1.4.6.0 # major.minor.patch.build
else:VERSION  = 1.4.6   # major.minor.patch
VERSION_STR = $$section(VERSION, ., 0, 2)

win32 {
    QMAKE_TARGET_COPYRIGHT = "LISE group at FRIB/MSU"
    QMAKE_TARGET_COMPANY   = "LISE group at FRIB/MSU"
}


# important to eliminate some LISEcute functions in IsomerAPI project
DEFINES += IsomerAPI_case

# Debug trace switch:
#   default: hide qDebug() output
#   enable : run qmake with ISOMERAPI_DEBUG_TRACE=1
isEmpty(ISOMERAPI_DEBUG_TRACE): ISOMERAPI_DEBUG_TRACE = 0
equals(ISOMERAPI_DEBUG_TRACE, 1) {
    DEFINES += ISOMERAPI_DEBUG_TRACE
    message("IsomerAPI qDebug trace output enabled")
} else {
    DEFINES += QT_NO_DEBUG_OUTPUT
    message("IsomerAPI qDebug trace output disabled")
}

# Sources
SOURCES += \
    g_Isomer/L_levelProxyModel.cpp \
    g_Isomer/d_ColumnsOptions.cpp \
    g_Isomer/d_DownloadFiles.cpp \
    g_Isomer/d_DrawingOptions.cpp \
    g_Isomer/d_TransmissionCalc.cpp \
    g_Isomer/iso_main.cpp \
    g_Isomer/o_cacheLevelProxy.cpp \
    g_Isomer/w_IsomerAPI.cpp \
    g_Isomer/w_IsomerAPI_drawing.cpp \
    g_Isomer/w_IsomerAPI_filters.cpp \
    g_Isomer/w_IsomerAPI_transmission.cpp \
    g_Isomer/w_aboutIsomerAPI.cpp \
    g_Isomer/w_schemeGraphic.cpp \
    g_Isomer/w_schemeWindow.cpp \
    w_Stuff/w_Label_clickable.cpp \
    w_Stuff/win_utilCalc.cpp \
    w_Stuff/win_utilPlot.cpp \
    w_Stuff/win_utilString.cpp

# Headers
HEADERS += \
    L_Init/Constant.h \
    g_Isomer/L_IsomerElement.h \
    g_Isomer/L_gammaProxyModel.h \
    g_Isomer/L_isoStructs.h \
    g_Isomer/L_isomerAPI_version.h \
    g_Isomer/L_levelProxyModel.h \
    g_Isomer/d_ColumnsOptions.h \
    g_Isomer/d_DownloadFiles.h \
    g_Isomer/d_DrawingOptions.h \
    g_Isomer/d_TransmissionCalc.h \
    g_Isomer/o_cacheLevelProxy.h \
    g_Isomer/w_IsomerAPI.h \
    g_Isomer/w_aboutIsomerAPI.h \
    g_Isomer/w_schemeGraphic.h \
    g_Isomer/w_schemeWindow.h \
    w_Stuff/liseStrcpyOS.h \
    w_Stuff/o_error_function.h \
    w_Stuff/w_Label_clickable.h

# UI forms
FORMS += \
    g_Isomer/d_ColumnsOptions.ui \
    g_Isomer/d_DownloadFiles.ui \
    g_Isomer/d_DrawingOptions.ui \
    g_Isomer/d_TransmissionCalc.ui \
    g_Isomer/w_IsomerAPI.ui \
    g_Isomer/w_aboutIsomerAPI.ui \
    g_Isomer/w_schemeWindow.ui

# Include path
INCLUDEPATH += $$PWD \
               $$PWD/../GLOBAL

# Database file (tracked for IDE, packaging, etc.)
# DISTFILES += database_store/Isomer_DB_WIDGET.sqlite

# Ensure database_store/ exists in build dir, then copy DB after build
# QMAKE_POST_LINK += $$QMAKE_MKDIR \"$$OUT_PWD/database_store\"
# QMAKE_POST_LINK += $$QMAKE_COPY \"$$PWD/database_store/Isomer_DB_WIDGET.sqlite\" \
#                                  \"$$OUT_PWD/database_store/Isomer_DB_WIDGET.sqlite\"

# Handle Qt version differences
# greaterThan(QT_MAJOR_VERSION, 5) {
#     message("Building with Qt6")
#     CONFIG += c++17
# } else {
#     message("Building with Qt5")
#     CONFIG += c++17
# }

# DISTFILES += \
#     _install/lisecfg/IsomerDB_Split.sqlite \
#     _install/lisecfg/Isomer_DB_WIDGET.sqlite \
#     _install/lisecfg/nndc_DB_fullScan.sqlite \
#     mainstyle.qss
#     mainstyle_light.qss

RESOURCES += \
    g_Isomer/isomapi_resources.qrc

DISTFILES += \
       Icons/IsomerAPI_icon.ico \
       Icons/clear.gif \
       Icons/clear.png \
       Icons/emblem_little_plus.png \
       Icons/gamma_decay2.png \
       Icons/gamma_decay3.png \
       Icons/isomerAPI-Logo.png \
       Icons/lisepp_small.bmp \
       Icons/nndcLogo.png \
       Icons/plot.png \
       Icons/trans.gif \
       _install/lisecfg/nndc_DB_fullScan.sqlite \
       g_Isomer/Icons/IsomerAPI_icon.ico

RC_ICONS +=  \
       g_Isomer/Icons/IsomerAPI_icon.ico



