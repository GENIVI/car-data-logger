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
 * \file HMIModeManager.h
*/

#ifndef HMIMODEMANAGER_H
#define HMIMODEMANAGER_H

#include <QObject>
#include <QSharedPointer>

#include <com/ivis/ModeManager/ModeManagerProxy.hpp>
#include <com/ivis/VehicleDataManager/VehicleDataManagerProxy.hpp>

using namespace v1::com::ivis::ModeManager;
using namespace v1::com::ivis::VehicleDataManager;

class QQuickView;
class QQmlContext;

enum MEDIA_TYPE{
    MEDIA_MUSIC_TYPE=0,
    MEDIA_VIDEO_TYPE,
};

class HMIModeManager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool lowFuelWarningState READ lowFuelWarningState WRITE setLowFuelWarningState NOTIFY lowFuelWarningStateChanged)

public:
    static QSharedPointer<HMIModeManager> instance (QObject *parent = Q_NULLPTR);
    ~HMIModeManager();

public:
    Q_INVOKABLE void init();

    Q_INVOKABLE void requestGoBack( QString requester );
    Q_INVOKABLE void requestGoMedia(int mediaType);


    void showMainView(QQuickView *view);
    void onActiveApplicationChanged(const ModeManagerTypes::ApplicationInfo & application);

    void onLowFuelWarningChanged(bool state);
    void onDrivingRestrictionChanged(bool state);

signals:
    void lowFuelWarningStateChanged(bool warningState);

private:
    explicit HMIModeManager(QObject *parent = Q_NULLPTR);

public:
    ModeManagerTypes::SubApplicationType mCurrentApplicationType;

    bool lowFuelWarningState() const;

public slots:
    void setLowFuelWarningState(bool warningState);

private:
    std::shared_ptr<ModeManagerProxy<>> mModeManagerProxy;    
    std::shared_ptr<VehicleDataManagerProxy<>> mVehicleDataManagerProxy;

    QQuickView *m_quickView;
    bool mLowFuelWarningState;
};

#endif // HMIMODEMANAGER_H
