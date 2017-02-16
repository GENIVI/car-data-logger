include(DataStoreHandler/datastorehandler.pri)
include(StorageManager/storagemanager.pri)
include(FileManager/filemanager.pri)
include(Configuration/configuration.pri)

HEADERS += \
    $$PWD/commonlogheader.h \
    $$PWD/storemanager.h

SOURCES += \
    $$PWD/storemanager.cpp

INCLUDEPATH += \
    $$PWD/Configuration \
    $$PWD/DataStoreHandler \
    $$PWD/FileManager \
    $$PWD/StorageManager \
