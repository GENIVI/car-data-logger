#-------------------------------------------------
#
# Project created by QtCreator 2016-12-02T10:16:34
#
#-------------------------------------------------

QT += core
QT -= gui

CONFIG += c++11
CONFIG += console
CONFIG -= app_bundle

TARGET = VSSCollectorTestApp
TEMPLATE = app

DEFINES += BOOST_ALL_DYN_LINK

SOURCES += main.cpp

INVITE_LIBS = vsi VSSDataCollector \

CONFIG += link_pkgconfig
PKGCONFIG += $$INVITE_LIBS

CONFIG(release, debug|release) {
    message( "release" )
    *-arm-* {
        message("arm!!")
        DESTDIR = release/arm
    }else{
        message("x86!!")
        DESTDIR = release/x86
    }
    DEFINES += __RELEASE__
}

CONFIG(debug, debug|release) {
    message( "debug" )
    *-arm-* {
        message("arm!!")
        DESTDIR = debug/arm
    }else{
        message("x86!!")
        DESTDIR = debug/x86
    }
    DEFINES += __DEBUG__
    QMAKE_CXXFLAGS += -g
}

OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR     = $$DESTDIR/.moc
RCC_DIR     = $$DESTDIR/.qrc
UI_DIR      = $$DESTDIR/.ui

target.path = ../deploy

INSTALLS += target

additional_files.files = vss_rel_1.json vss_rel_1.vsi DataConfig.json
additional_files.path = ../deploy

INSTALLS += additional_files

