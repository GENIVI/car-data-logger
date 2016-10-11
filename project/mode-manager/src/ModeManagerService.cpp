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
 * \file ModeManagerService.cpp
*/

#include "ModeManagerService.h"
#include "ModeManagerDebug.h"
#include "LogHelper.h"

#include <QDebug>

DLT_IMPORT_CONTEXT( ContextModeManager )

std::shared_ptr<ModeManageService> modeManagerInstance = nullptr;

std::shared_ptr<ModeManageService> &ModeManageService::getInstance()
{
    if ( modeManagerInstance == nullptr )
        modeManagerInstance = std::shared_ptr<ModeManageService>( new ModeManageService );

    return modeManagerInstance;
}

ModeManageService::ModeManageService( QObject *parent )
    : QObject( parent ),
      ModeManagerStubDefault(),
      m_appInfo(),
      m_requester()
{
    m_appInfo.setApp( ModeManagerTypes::ApplicationType::APP_NONE );
    m_appInfo.setSubApp( ModeManagerTypes::SubApplicationType::SUB_APP_NONE );
    initLastSubAppInfo(eLastSubSource::LAST_SUB_SOURCE_USB_AUDIO);
}

void ModeManageService::setAppInfo( const ModeManagerTypes::ApplicationInfo &appInfo )
{
    m_appInfo = appInfo;
}

void ModeManageService::setRequester( ModeManagerTypes::AppChangeRequester requester )
{
    m_requester = requester;
}








/* Needed Source Code */
void ModeManageService::setActiveApplicationAttribute( ModeManagerTypes::ApplicationInfo value )
{
    LogHelper log( Q_FUNC_INFO );
    log.print( QString( "value = %1" ).arg( DebugHelper::toString( value ) ) );

    ModeManagerStubDefault::setActiveApplicationAttribute( value );
}

void ModeManageService::requestChangeApplication( ModeManagerTypes::ApplicationType app, ModeManagerTypes::SubApplicationType subApp, ModeManagerTypes::AppChangeRequester requester )
{
    ModeManagerTypes::ApplicationInfo requestAppInfo = ModeManagerTypes::ApplicationInfo();
    requestAppInfo.setApp( app );
    requestAppInfo.setSubApp( subApp );

    m_requester = requester;

    m_appInfo.setApp( app );
    m_appInfo.setSubApp( subApp );

    /* Needed Source Code */
    setActiveApplicationAttribute( m_appInfo );

    /* Needed for Suite HMI_Application */
    fireActiveApplicationChangedEvent(m_appInfo, m_requester);

    fireResponseChangeApplicationEvent( ModeManagerTypes::AppChangeResult::RESULT_OK, m_appInfo, requestAppInfo, requester );
}






void ModeManageService::initLastSubAppInfo( const eLastSubSource &subSource )
{
    switch ( subSource )
    {
    case eLastSubSource::LAST_SUB_SOURCE_USB_VIDEO:
        m_appInfo.setSubApp( ModeManagerTypes::SubApplicationType::SUB_APP_VIDEO );
        break;

    case eLastSubSource::LAST_SUB_SOURCE_USB_AUDIO:
    case eLastSubSource::LAST_SUB_SOURCE_RADIO_AUDIO:
    case eLastSubSource::LAST_SUB_SOURCE_BLUTOOTH_AUDIO:
    default:
        m_appInfo.setSubApp( ModeManagerTypes::SubApplicationType::SUB_APP_AUDIO );
        break;
    }
}

void ModeManageService::requestChangeApplication( const std::shared_ptr<CommonAPI::ClientId> _client, ::v1::com::ivis::ModeManager::ModeManagerTypes::ApplicationType _app, ::v1::com::ivis::ModeManager::ModeManagerTypes::SubApplicationType _subApp, ::v1::com::ivis::ModeManager::ModeManagerTypes::AppChangeRequester _requester, requestChangeApplicationReply_t _reply )
{
    Q_UNUSED( _client );

    requestChangeApplication( _app, _subApp, _requester );

    _reply();
}

void ModeManageService::fireResponseChangeApplicationEvent( const ModeManagerTypes::AppChangeResult &result, const ModeManagerTypes::ApplicationInfo &currentAppInfo, const ModeManagerTypes::ApplicationInfo &requestAppInfo, const ModeManagerTypes::AppChangeRequester &requester )
{
    LogHelper log( Q_FUNC_INFO );
    log.print( QString( "result = %1" ).arg( DebugHelper::toString( result ) ) );
    log.print( QString( "currentAppInfo = %1" ).arg( DebugHelper::toString( currentAppInfo ) ) );
    log.print( QString( "requestAppInfo = %1" ).arg( DebugHelper::toString( requestAppInfo ) ) );
    log.print( QString( "requester = %1" ).arg( DebugHelper::toString( requester ) ) );

    ModeManagerStubDefault::fireResponseChangeApplicationEvent( result, currentAppInfo, requestAppInfo, requester );
}

void ModeManageService::fireActiveApplicationChangedEvent( const ModeManagerTypes::ApplicationInfo &appInfo, const ModeManagerTypes::AppChangeRequester &requester )
{
    LogHelper log( Q_FUNC_INFO );
    log.print( QString( "appInfo = %1" ).arg( DebugHelper::toString( appInfo ) ) );
    log.print( QString( "requester = %1" ).arg( DebugHelper::toString( requester ) ) );

    ModeManagerStubDefault::fireActiveApplicationChangedEvent( appInfo, requester );
}
