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
 * \file CDLClientRemoteAPI.h
*/

#ifndef CDLCLIENTREMOTEAPI_H
#define CDLCLIENTREMOTEAPI_H

#include "CDLClientProxyBase.h"

#include <QObject>
#include <com/ivis/CDL/ClientAPIRemoteProxy.hpp>

using namespace v1::com::ivis::CDL;

class CDLClientRemoteAPI : public ICDLClientAPI
{

public:
    static std::shared_ptr<CDLClientRemoteAPI> &getInstance();

    void init();

    CDL::CDLError storeData(std::string domain, std::string subDomain, std::string id, CDL::CDLData data);
    CDL::CDLError registerNotifyCallback(CDL::notifyCallback callback);

    void onCDLDataEvent(std::string domain, std::string subDomain, std::string id, CDL::CDLData data);

private:
    CDLClientRemoteAPI();

    std::shared_ptr< ClientAPIRemoteProxy<> > m_clientProxy;
};

#endif // CDLCLIENTREMOTEAPI_H
