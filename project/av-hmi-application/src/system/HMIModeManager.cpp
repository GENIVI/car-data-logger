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
 * \file HMIModeManager.cpp
*/

#include "HMIModeManager.h"
#include "MainWindow.h"
#include "DATCControl.h"
#include "MusicPlayControl.h"
#include "VideoPlayControl.h"

#include <QQuickView>
#include <QQmlContext>
#include <QDebug>
#include <CommonAPI/CommonAPI.hpp>

static QSharedPointer<HMIModeManager> hmiModeManagerInstance;

QSharedPointer<HMIModeManager> HMIModeManager::instance(QObject *parent)
{
    if (hmiModeManagerInstance.isNull())
    {
        hmiModeManagerInstance =  QSharedPointer<HMIModeManager>(new HMIModeManager(parent));
    }

    return hmiModeManagerInstance;
}

HMIModeManager::~HMIModeManager()
{    

}

void HMIModeManager::init()
{
    qDebug("HMIModeManager Init()");

    auto runtime = CommonAPI::Runtime::get();

    mModeManagerProxy = runtime->buildProxy<ModeManagerProxy>("local", "com.ivis.ModeManager.ModeManager");
    mVehicleDataManagerProxy = runtime->buildProxy<VehicleDataManagerProxy>("local", "com.ivis.VehicleDataManager.VehicleDataManager");

    mModeManagerProxy->getActiveApplicationAttribute().getChangedEvent().subscribe(
                std::bind(&HMIModeManager::onActiveApplicationChanged, this, std::placeholders::_1));

    mVehicleDataManagerProxy->getDrivingRestrictionAttribute().getChangedEvent().subscribe(
                std::bind(&HMIModeManager::onDrivingRestrictionChanged, this, std::placeholders::_1));

    mVehicleDataManagerProxy->getLowFuelWarningAttribute().getChangedEvent().subscribe(
                std::bind(&HMIModeManager::onLowFuelWarningChanged, this, std::placeholders::_1));
}

void HMIModeManager::requestGoBack(QString requester)
{
    Q_UNUSED(requester)
}

void HMIModeManager::requestGoMedia(int mediaType)
{
    switch(mediaType)
    {
    case MEDIA_MUSIC_TYPE:
        mModeManagerProxy->requestChangeApplicationAsync(ModeManagerTypes::ApplicationType::APP_USB,
                                                         ModeManagerTypes::SubApplicationType::SUB_APP_AUDIO,
                                                         ModeManagerTypes::AppChangeRequester::BY_HMI);

        break;

    case MEDIA_VIDEO_TYPE:
        mModeManagerProxy->requestChangeApplicationAsync(ModeManagerTypes::ApplicationType::APP_USB,
                                                         ModeManagerTypes::SubApplicationType::SUB_APP_VIDEO,
                                                         ModeManagerTypes::AppChangeRequester::BY_HMI);

        break;
    }
}

void HMIModeManager::onActiveApplicationChanged(const ModeManagerTypes::ApplicationInfo &application)
{
    mCurrentApplicationType = application.getSubApp();
}

void HMIModeManager::onLowFuelWarningChanged(bool state)
{
    setLowFuelWarningState(state);
}

void HMIModeManager::onDrivingRestrictionChanged(bool state)
{
    VideoPlayControl::instance()->setDriveRestrict(state);
}

HMIModeManager::HMIModeManager(QObject *parent)
    : QObject(parent)
{
    setObjectName("HMIModeManager");

    mCurrentApplicationType = ModeManagerTypes::SubApplicationType::SUB_APP_NONE;

    init();
}




bool HMIModeManager::lowFuelWarningState() const
{
    return mLowFuelWarningState;
}

void HMIModeManager::setLowFuelWarningState(bool warningState)
{
    if (mLowFuelWarningState == warningState)
        return;

    mLowFuelWarningState = warningState;
    emit lowFuelWarningStateChanged(warningState);
}
