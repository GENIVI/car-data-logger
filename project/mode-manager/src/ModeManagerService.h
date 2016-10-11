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
 * \file ModeManagerService.h
*/

#ifndef MODEMANAGESERVICE_H
#define MODEMANAGESERVICE_H

#include <QObject>
#include <com/ivis/ModeManager/ModeManagerStubDefault.hpp>
#include "ModeDefine.h"

using namespace v1::com::ivis::ModeManager;

class ModeManageService : public QObject, public ModeManagerStubDefault
{
    Q_OBJECT
public:
    static std::shared_ptr<ModeManageService> &getInstance();

    void initLastSubAppInfo( const eLastSubSource &subSource );


    const ModeManagerTypes::ApplicationInfo &getAppInfo() { return m_appInfo; }


    void setAppInfo( const ModeManagerTypes::ApplicationInfo &appInfo );
    void setRequester( ModeManagerTypes::AppChangeRequester requester );


    void setActiveApplicationAttribute( ModeManagerTypes::ApplicationInfo value );
    void requestChangeApplication( ModeManagerTypes::ApplicationType app, ModeManagerTypes::SubApplicationType subApp, ModeManagerTypes::AppChangeRequester requester );


public:
    /* ModeManagerStubDefault interface */
    virtual void requestChangeApplication( const std::shared_ptr<CommonAPI::ClientId> _client, ::v1::com::ivis::ModeManager::ModeManagerTypes::ApplicationType _app, ::v1::com::ivis::ModeManager::ModeManagerTypes::SubApplicationType _subApp, ::v1::com::ivis::ModeManager::ModeManagerTypes::AppChangeRequester _requester, requestChangeApplicationReply_t _reply );

    /* ModeManagerStub interface */
    void fireResponseChangeApplicationEvent( const ModeManagerTypes::AppChangeResult &result, const ModeManagerTypes::ApplicationInfo &currentAppInfo, const ModeManagerTypes::ApplicationInfo &requestAppInfo, const ModeManagerTypes::AppChangeRequester &requester );
    void fireActiveApplicationChangedEvent( const ModeManagerTypes::ApplicationInfo &appInfo, const ModeManagerTypes::AppChangeRequester &requester );

private:
    explicit ModeManageService( QObject *parent = 0 );

    ModeManagerTypes::ApplicationInfo m_appInfo;

    ModeManagerTypes::AppChangeRequester m_requester;
};


#endif // MODEMANAGESERVICE_H
