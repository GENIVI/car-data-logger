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
 * \file CDLDaemon.h
*/

#ifndef CDLDAEMON
#define CDLDAEMON

#include <QObject>
#include "dlt.h"

#include "com/ivis/CDL/ClientAPILocalStubDefault.hpp"
#include "com/ivis/CDL/ClientAPIRemoteStubDefault.hpp"

using namespace v1::com::ivis::CDL;

class CDLLocalAPIHandler : public ClientAPILocalStubDefault
{
public:
    static std::shared_ptr < CDLLocalAPIHandler > &getInstance();
    static void finalize();

private:
    CDLLocalAPIHandler( );
    Q_DISABLE_COPY(CDLLocalAPIHandler)

public:
    virtual ~CDLLocalAPIHandler();

private:
    virtual void storeData(const std::shared_ptr<CommonAPI::ClientId> _client, std::string _domain, std::string _subDomain, std::string _id, ClientAPILocalTypes::CDLData _data, storeDataReply_t _reply) override;

private:
    DLT_DECLARE_CONTEXT(mLocalContext)
};



class CDLRemoteAPIHandler : public ClientAPIRemoteStubDefault
{
public:
    static std::shared_ptr < CDLRemoteAPIHandler > &getInstance();
    static void finalize();

private:
    CDLRemoteAPIHandler( );
    Q_DISABLE_COPY(CDLRemoteAPIHandler)

public:
    virtual ~CDLRemoteAPIHandler();

private:
    virtual void storeData(const std::shared_ptr<CommonAPI::ClientId> _client, std::string _domain, std::string _subDomain, std::string _id, ClientAPIRemoteTypes::CDLData _data, storeDataReply_t _reply) override;

private:
    DLT_DECLARE_CONTEXT(mRemoteContext)
};




class CDLDaemon
{
public:
    static CDLDaemon* getInstance();
    static void finalize();

private:
    CDLDaemon( );

public:
    ~CDLDaemon();

public:
    void storeData(std::string _domain, std::string _subDomain, std::string _id, ClientAPIRemoteTypes::CDLData _data);

private:
    DLT_DECLARE_CONTEXT(mDaemonContext)
};

#endif // CDLDAEMON
