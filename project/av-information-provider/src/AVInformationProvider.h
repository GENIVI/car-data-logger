/*
 * Copyright (C) 2016, IVIS
 *
 * This file is part of GENIVI Project CDL - Car Data Logger.
 *
 * This Source Code Form is subject to the terms of the
 * Mozilla Public License (MPL), v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * For further information see http://www.genivi.org/.
 */

/*!
 * \author Seung-Hyun Yun <shyun@ivisolution.com>
 *
 * \copyright Copyright (c) 2016, IVIS \n
 * License MPL-2.0: Mozilla Public License version 2.0 http://mozilla.org/MPL/2.0/.
 *
 * \file AVInformationProvider.h
*/

#ifndef AVINFORMATIONPROVIDER
#define AVINFORMATIONPROVIDER

#include <QObject>

#include <com/ivis/AVInformationProvider/AVInformationStubDefault.hpp>
#include <com/ivis/MediaManager/PlaybackControlProxy.hpp>
#include <com/ivis/ModeManager/ModeManagerProxy.hpp>

#include <dlt.h>

using namespace v1::com::ivis::AVInformationProvider;
using namespace v1::com::ivis::MediaManager;
using namespace v1::com::ivis::ModeManager;

class AVInformationProvider : public QObject
{
    Q_OBJECT

public:
    AVInformationProvider(QObject * parent);
    virtual ~AVInformationProvider();

public:
    // for mode manager
    void activeApplicationChanged(const ModeManagerTypes::ApplicationInfo & activeApplicationInfo);

    // for playback
    void currentTrackInfoChanged(const MediaManagerTypes::TrackInfo & trackInfo);
    void currentTrackNumberChanged(uint32_t currentTrackNumber);
    void totalTrackNumberChanged(uint32_t totalTrackNumber);
    void playStateChanged(const MediaManagerTypes::PlayStateInfo & playStateInfo);
    void timePositionInfoChanged(const MediaManagerTypes::TimePositionInfo & timePositionInfo);

private:
    void load_image_resize(/*const*/ QString image_filename);
    void send_image(std::vector<uint8_t> & data);

private:
    std::shared_ptr<ModeManagerProxy<> > mModeManager;
    std::shared_ptr<PlaybackControlProxy<> > mPlayback;
    std::shared_ptr<AVInformationStubDefault> mAVInformation;

    std::vector<uint8_t> mBuffer;
    AVInformationTypes::Source m_source;

    DLT_DECLARE_CONTEXT(mContext)
};

#endif // AVINFORMATIONPROVIDER

