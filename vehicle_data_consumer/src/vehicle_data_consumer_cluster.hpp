/*
* Copyright (C) 2017, IVIS
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
* \author Seok-Heum Choi <seokheum.choi@ivisolution.com>
*
* \copyright Copyright (c) 2017, IVIS \n
* License MPL-2.0: Mozilla Public License version 2.0 http://mozilla.org/MPL/2.0/.
*
*/

#ifndef VEHICLEDATACONSUMERCLUSTER_H
#define VEHICLEDATACONSUMERCLUSTER_H

#include <org/genivi/CDL/ClientAPIProxy.hpp>
#include <com/ivis/ClusterData/ClusterDataStubDefault.hpp>

#include <vector>

using namespace std;
using namespace v1::org::genivi::CDL;
using namespace v1::com::ivis::ClusterData;

class ClientAuthenticationEncryptionHandler;

class VehicleDataConsumerCluster
{
public:
    VehicleDataConsumerCluster();
    virtual ~VehicleDataConsumerCluster();

private:
    void init();
    void initLog();
    virtual void createProxy();
    void subscribeEvents();
    void onConnectionsStatusChanged(CommonAPI::AvailabilityStatus status);
    void onNotifyData(const std::string &_id, const ClientAPITypes::Types &_type, const std::string &_unit, const ClientAPITypes::CDLValue &_value, const uint64_t &_timeStamp);
    bool registerClient();

private:
    std::shared_ptr<ClientAPIProxy<>> m_proxy;
    std::shared_ptr<ClusterDataStubDefault> m_clusterDataService;
    ClientAPITypes::Handle m_handle;
    ClientAPITypes::NotifyType m_notiType;
    vector<string> m_requestIDList;

    ClientAuthenticationEncryptionHandler * m_clientAuthenticationEncryptionHandler;
    string m_publicKey;
};

#endif // VEHICLEDATACONSUMERCLUSTER_H
