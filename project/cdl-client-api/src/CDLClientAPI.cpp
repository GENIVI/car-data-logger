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
 * \file CDLClientAPI.cpp
*/

#include "cdl/CDLClientAPI.h"
#include "CDLClientLocalAPI.h"
#include "CDLClientRemoteAPI.h"

#include <QDebug>

namespace CDL
{

static ICDLClientAPI *m_proxy = nullptr;

CDLError initClientAPI(CDLRuntimeType type)
{
    if(type == CDLRuntimeType::RUNTIME_DBUS)
    {
        m_proxy = CDLClientLocalAPI::getInstance().get();
    }
    else if(type == CDLRuntimeType::RUNTIME_SOMEIP)
    {
        m_proxy = CDLClientRemoteAPI::getInstance().get();
    }
    else
    {
        return CDL_ERROR;
    }

    return CDL_OK;
}

CDLError storeData(std::string domain, std::string subDomain, std::string id, CDLData data)
{
    return m_proxy->storeData(domain, subDomain, id, data);
}

CDLError registerNotifyCallback(notifyCallback callback)
{
    return m_proxy->registerNotifyCallback(callback);
}

}

ICDLClientAPI::ICDLClientAPI() : fireCDLDataCallback(nullptr)
{

}
