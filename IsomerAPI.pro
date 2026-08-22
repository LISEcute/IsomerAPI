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

win32:VERSION = 1.4.2.0 # major.minor.patch.build
else:VERSION  = 1.4.2   # major.minor.patch
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
    w_Isomer/L_levelProxyModel.cpp \
    w_Isomer/d_ColumnsOptions.cpp \
    w_Isomer/d_DownloadFiles.cpp \
    w_Isomer/d_DrawingOptions.cpp \
    w_Isomer/d_TransmissionCalc.cpp \
    w_Isomer/iso_main.cpp \
    w_Isomer/o_cacheLevelProxy.cpp \
    w_Isomer/w_IsomerAPI.cpp \
    w_Isomer/w_IsomerAPI_drawing.cpp \
    w_Isomer/w_IsomerAPI_filters.cpp \
    w_Isomer/w_IsomerAPI_transmission.cpp \
    w_Isomer/w_aboutIsomerAPI.cpp \
    w_Isomer/w_schemeGraphic.cpp \
    w_Isomer/w_schemeWindow.cpp \
    w_Stuff/w_Label_clickable.cpp \
    w_Stuff/win_utilCalc.cpp \
    w_Stuff/win_utilPlot.cpp \
    w_Stuff/win_utilString.cpp

# Headers
HEADERS += \
    w_Isomer/L_IsomerElement.h \
    w_Isomer/L_gammaProxyModel.h \
    w_Isomer/L_isoStructs.h \
    w_Isomer/L_isomerAPI_version.h \
    w_Isomer/L_levelProxyModel.h \
    w_Isomer/d_ColumnsOptions.h \
    w_Isomer/d_DownloadFiles.h \
    w_Isomer/d_DrawingOptions.h \
    w_Isomer/d_TransmissionCalc.h \
    w_Isomer/o_cacheLevelProxy.h \
    w_Isomer/w_IsomerAPI.h \
    w_Isomer/w_aboutIsomerAPI.h \
    w_Isomer/w_schemeGraphic.h \
    w_Isomer/w_schemeWindow.h \
    w_Stuff/liseStrcpyOS.h \
    w_Stuff/o_error_function.h \
    w_Stuff/w_Label_clickable.h

# UI forms
FORMS += \
    w_Isomer/d_ColumnsOptions.ui \
    w_Isomer/d_DownloadFiles.ui \
    w_Isomer/d_DrawingOptions.ui \
    w_Isomer/d_TransmissionCalc.ui \
    w_Isomer/w_IsomerAPI.ui \
    w_Isomer/w_aboutIsomerAPI.ui \
    w_Isomer/w_schemeWindow.ui

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
    w_Isomer/isomapi_resources.qrc

DISTFILES += \
       _install/lisecfg/nndc_DB_fullScan.sqlite \
       w_Isomer/Icons/IsomerAPI_icon.ico

RC_ICONS +=  \
       w_Isomer/Icons/IsomerAPI_icon.ico



