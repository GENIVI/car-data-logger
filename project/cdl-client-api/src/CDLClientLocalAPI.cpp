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
 * \file CDLClientLocalAPI.cpp
*/

#include "CDLClientLocalAPI.h"
#include <QDebug>

std::shared_ptr<CDLClientLocalAPI> mCDLClientLocalAPISharedPtr = NULL;

CDLClientLocalAPI::CDLClientLocalAPI() : ICDLClientAPI()
{

}

std::shared_ptr<CDLClientLocalAPI> &CDLClientLocalAPI::getInstance()
{
    if (!mCDLClientLocalAPISharedPtr)
    {
        mCDLClientLocalAPISharedPtr = std::shared_ptr<CDLClientLocalAPI> (new CDLClientLocalAPI);
        mCDLClientLocalAPISharedPtr.get()->init();
    }

    return mCDLClientLocalAPISharedPtr;
}

void CDLClientLocalAPI::init()
{
    std::shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();
    m_clientProxy = runtime->buildProxy<ClientAPILocalProxy>("local", v1_0::com::ivis::CDL::ClientAPILocal::getInterface());
}

CDL::CDLError CDLClientLocalAPI::storeData(std::string domain, std::string subDomain, std::string id, CDL::CDLData data)
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

CDL::CDLError CDLClientLocalAPI::registerNotifyCallback(CDL::notifyCallback callback)
{
    fireCDLDataCallback = callback;
    if (m_clientProxy != nullptr)
    {
        m_clientProxy.get()->getNotifyDataEvent().subscribe(
            std::bind(&CDLClientLocalAPI::onCDLDataEvent, this,
                      std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
        return CDL::CDLError::CDL_OK;
    }
    else
    {
        return CDL::CDLError::CDL_ERROR;
    }
}

void CDLClientLocalAPI::onCDLDataEvent(std::string domain, std::string subDomain, std::string id, CDL::CDLData data)
{
    if (fireCDLDataCallback) fireCDLDataCallback(domain, subDomain, id, data);
}
