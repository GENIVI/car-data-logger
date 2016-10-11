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
 * \file VehicleDataConsumerCluster.h
*/

#ifndef VEHICLEDATACONSUMER_H
#define VEHICLEDATACONSUMER_H

#include <cdl/CDLClientAPI.h>
#include <com/ivis/ClusterData/ClusterDataStubDefault.hpp>
#include <dlt.h>

using namespace v1::com::ivis::ClusterData;

class VehicleDataConsumerCluster
{
public:
    static VehicleDataConsumerCluster * instance();
    static void finalize();

    ~VehicleDataConsumerCluster();

private:
    VehicleDataConsumerCluster();

public:
    void onCDLData(std::string domain, std::string sub_domain, std::string id, CDL::CDLData data);

private:
    void initClusterDataService();
    void initCDLClientAPI();

    void processRunningStatusData(std::string id, CDL::CDLData & data);
    void processVehicleSpeedData(CDL::CDLData & data);
    void processEngineSpeedData(CDL::CDLData & data);
    void processFuelLevelData(CDL::CDLData & data);

private:
    std::shared_ptr<ClusterDataStubDefault> mClusterDataService;

    DLT_DECLARE_CONTEXT(mContext)
};

#endif // VEHICLEDATACONSUMER_H
