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
 * \file CDLClientRemoteAPI.cpp
*/

#include "CDLClientRemoteAPI.h"
#include <QDebug>

std::shared_ptr<CDLClientRemoteAPI> mCDLClientRemoteAPISharedPtr = NULL;

CDLClientRemoteAPI::CDLClientRemoteAPI() : ICDLClientAPI()
{

}

std::shared_ptr<CDLClientRemoteAPI> &CDLClientRemoteAPI::getInstance()
{
    if (!mCDLClientRemoteAPISharedPtr)
    {
        mCDLClientRemoteAPISharedPtr = std::shared_ptr<CDLClientRemoteAPI> (new CDLClientRemoteAPI);
        mCDLClientRemoteAPISharedPtr.get()->init();
    }

    return mCDLClientRemoteAPISharedPtr;
}

void CDLClientRemoteAPI::init()
{
    std::shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();
    m_clientProxy = runtime->buildProxy<ClientAPIRemoteProxy>("local", "com.ivis.CDL.ClientAPIRemote.SomeIp");
}

CDL::CDLError CDLClientRemoteAPI::storeData(std::string domain, std::string subDomain, std::string id, CDL::CDLData data)
{
    if (m_clientProxy != nullptr)
    {
        CommonAPI::CallStatus callStatus = CommonAPI::CallStatus::SUCCESS;
        const CommonAPI::CallInfo *callInfo = nullptr;
        m_clientProxy.get()->storeData(domain, subDomain, id, data, callStatus, callInfo);
        return CDL::CDLError::CDL_OK;
    }
    else
    {
        return CDL::CDLError::CDL_ERROR;
    }
}

CDL::CDLError CDLClientRemoteAPI::registerNotifyCallback(CDL::notifyCallback callback)
{
    fireCDLDataCallback = callback;
    if (m_clientProxy != nullptr)
    {
        m_clientProxy.get()->getNotifyDataEvent().subscribe(
            std::bind(&CDLClientRemoteAPI::onCDLDataEvent, this,
                      std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
        return CDL::CDLError::CDL_OK;
    }
    else
    {
        return CDL::CDLError::CDL_ERROR;
    }
}

void CDLClientRemoteAPI::onCDLDataEvent(std::string domain, std::string subDomain, std::string id, CDL::CDLData data)
{
    if (fireCDLDataCallback) fireCDLDataCallback(domain, subDomain, id, data);
}
