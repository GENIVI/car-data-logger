#ifndef MEDIA_COMMON_ENUM_H
#define MEDIA_COMMON_ENUM_H

#include <QObject>

class MediaCommonEnum : public QObject
{
    Q_OBJECT

    Q_ENUMS(MEDIA_PLAY_TYPE)
    Q_ENUMS(TOUCH_SIGNAL_TYPE)
public:
    enum MEDIA_PLAY_TYPE{
        MUSIC_PLAY_TYPE=0,
        VIDEO_PLAY_TYPE,
    };

    enum TOUCH_SIGNAL_TYPE{
        TOUCH_SIGNAL_PRESSED=0,
        TOUCH_SIGNAL_PRESSED_LONG,
        TOUCH_SIGNAL_RELEASED,
    };
};

#endif // COMMON_ENUM_H
