include(VssJsonService/vssjsonservice.pri)
include(DataConfigService/dataconfigservice.pri)
include(VSIWatcher/vsiwatcher.pri)

HEADERS += \
    $$PWD/vssdatacollector.h \
    $$PWD/commonlogheader.h \

SOURCES += \
    $$PWD/vssdatacollector.cpp

