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
 * \file AVInformationProviderHelper.h
*/

#ifndef AVINFORMATIONPROVIDERHELPER_H
#define AVINFORMATIONPROVIDERHELPER_H

#include <QObject>
#include <QLoggingCategory>

#ifdef ENABLE_COMMONAPI
    #include <CommonAPI/CommonAPI.hpp>
    #include "com/ivis/AVInformationProvider/AVInformationProxy.hpp"

    using namespace v1::com::ivis::AVInformationProvider;
#endif

Q_DECLARE_LOGGING_CATEGORY(avInformationProviderHelper)

class AVInformationProviderHelper : public QObject
{
    Q_OBJECT

public:
#ifdef ENABLE_COMMONAPI
    static std::shared_ptr<AVInformationProviderHelper> &getInstance();
#endif
    static void finalize();

private:
    explicit AVInformationProviderHelper(QObject *parent = Q_NULLPTR);

#ifdef ENABLE_COMMONAPI
    void init();
    void subscribeEvents();

    void onCurrentSourceChanged(AVInformationTypes::Source source);
    void onMetaDataChanged(AVInformationTypes::MetaData metaData);
    void onPlayPositionChanged(AVInformationTypes::PlayPosition playPosition);
    void onPlayStatusChanged(AVInformationTypes::PlayStatus playStatus);
    void onAlbumArtEvent(uint32_t totalSegmentCount, uint32_t currentIndex, std::vector<uint8_t> imageData);
#endif

private:
#ifdef ENABLE_COMMONAPI
    std::shared_ptr< AVInformationProxy<> > m_AVInfoProxy;
    std::vector<uint8_t> gImageBuffer;
    uint32_t mPrevCoverArtIndex;
#endif

};

#endif // AVINFORMATIONPROVIDERHELPER_H
