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
 * \file CDLDaemon.cpp
*/

#include "CDLDaemon.h"

#include "DBHandler.h"

std::shared_ptr< CDLLocalAPIHandler > localAPIInstance = nullptr;
std::shared_ptr< CDLRemoteAPIHandler > remoteAPIInstance = nullptr;

CDLDaemon* cdlDaemonInstance = nullptr;

std::shared_ptr<CDLLocalAPIHandler> &CDLLocalAPIHandler::getInstance()
{
    if ( localAPIInstance == nullptr )
    {
        localAPIInstance = std::shared_ptr<CDLLocalAPIHandler> (new CDLLocalAPIHandler);
    }
    return localAPIInstance;
}

void CDLLocalAPIHandler::finalize()
{
    localAPIInstance = nullptr;
}

CDLLocalAPIHandler::CDLLocalAPIHandler()
     : ClientAPILocalStubDefault()
{
    DLT_REGISTER_CONTEXT( mLocalContext, "cdml", "CDL Daemon Local" );
    DLT_LOG( mLocalContext, DLT_LOG_INFO, DLT_STRING(" Construct Local API ") );
}

CDLLocalAPIHandler::~CDLLocalAPIHandler()
{
    DLT_UNREGISTER_CONTEXT( mLocalContext );

    CDLDaemon::finalize();
}

void CDLLocalAPIHandler::storeData(const std::shared_ptr<CommonAPI::ClientId> _client, std::string _domain, std::string _subDomain, std::string _id, ClientAPILocalTypes::CDLData _data, ClientAPILocalStub::storeDataReply_t _reply)
{
    Q_UNUSED( _client );

    CDLDaemon::getInstance()->storeData( _domain, _subDomain, _id, _data );

    _reply();
}







std::shared_ptr<CDLRemoteAPIHandler> &CDLRemoteAPIHandler::getInstance()
{
    if ( remoteAPIInstance == nullptr )
    {
        remoteAPIInstance = std::shared_ptr<CDLRemoteAPIHandler> (new CDLRemoteAPIHandler);
    }
    return remoteAPIInstance;
}

void CDLRemoteAPIHandler::finalize()
{
    remoteAPIInstance = nullptr;
}

CDLRemoteAPIHandler::CDLRemoteAPIHandler()
    : ClientAPIRemoteStubDefault()
{
    DLT_REGISTER_CONTEXT( mRemoteContext, "cdmr", "CDL Daemon Remote" );
    DLT_LOG( mRemoteContext, DLT_LOG_INFO, DLT_STRING(" Construct Remote API ") );
}

CDLRemoteAPIHandler::~CDLRemoteAPIHandler()
{
    DLT_UNREGISTER_CONTEXT( mRemoteContext );

    CDLDaemon::finalize();
}

void CDLRemoteAPIHandler::storeData(const std::shared_ptr<CommonAPI::ClientId> _client, std::string _domain, std::string _subDomain, std::string _id, ClientAPIRemoteTypes::CDLData _data, ClientAPIRemoteStub::storeDataReply_t _reply)
{
    Q_UNUSED( _client );

    CDLDaemon::getInstance()->storeData( _domain, _subDomain, _id, _data );

    _reply();
}







CDLDaemon *CDLDaemon::getInstance()
{
    if( cdlDaemonInstance == nullptr)
    {
        cdlDaemonInstance = new CDLDaemon();
    }
    return cdlDaemonInstance;
}

void CDLDaemon::finalize()
{
    if ( cdlDaemonInstance != nullptr )
    {
        delete cdlDaemonInstance;
        cdlDaemonInstance = nullptr;
    }
}

CDLDaemon::CDLDaemon()
{
    DLT_REGISTER_CONTEXT( mDaemonContext, "cdmn", "CDL Daemon" );
}

CDLDaemon::~CDLDaemon()
{
    DLT_UNREGISTER_CONTEXT( mDaemonContext );
}


void CDLDaemon::storeData(std::string _domain, std::string _subDomain, std::string _id, ClientAPIRemoteTypes::CDLData _data)
{
    // Database
    DBHandler::instance()->storeData( _domain, _subDomain, _id, _data );

    // Notify (D-BUS)
    CDLLocalAPIHandler::getInstance()->fireNotifyDataEvent( _domain, _subDomain, _id, _data );
    // Notify (SOMEIP)
    CDLRemoteAPIHandler::getInstance()->fireNotifyDataEvent( _domain, _subDomain, _id, _data );
}
