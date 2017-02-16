#-------------------------------------------------
#
# Project created by QtCreator 2017-01-19T13:59:22
#
#-------------------------------------------------

QT += core
QT -= gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG += console
CONFIG -= app_bundle

TARGET = DataStoreTestApp
TEMPLATE = app

DEFINES += BOOST_ALL_DYN_LINK

SOURCES += \
        main.cpp\
        vehicledatagenerator.cpp \

HEADERS  += \
    vehicledatagenerator.h \

INVITE_LIBS = DataStoreManager \

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

additional_files.files = store_config_file.json
additional_files.path = ../deploy

INSTALLS += additional_files
