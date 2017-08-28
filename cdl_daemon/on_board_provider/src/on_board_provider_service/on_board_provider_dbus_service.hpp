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

#ifndef ONBOARDPROVIDERDBUSSERVICE_H
#define ONBOARDPROVIDERDBUSSERVICE_H

#include "on_board_provider_service.hpp"

typedef OnBoardProviderService::RuntimeType RunTimeType;

/**
 * @brief Received the requested information/data using ClientAPI interface from the DBus type client.
 *
 */

class OnBoardProviderDBusService : public ClientAPIStubDefault
{
public:
    OnBoardProviderDBusService(OnBoardProviderService * onBoardProviderService);
    virtual ~OnBoardProviderDBusService();

public:
    virtual void registerClient(const std::shared_ptr<CommonAPI::ClientId> _client, std::string _key, registerClientReply_t _reply);
    virtual void setListenData(const std::shared_ptr<CommonAPI::ClientId> _client, ClientAPITypes::Handle _handle, std::vector<std::string> _signalNameList, ClientAPITypes::NotifyType _type, setListenDataReply_t _reply);
    virtual void getData(const std::shared_ptr<CommonAPI::ClientId> _client, ClientAPITypes::Handle _handle, std::string _signalName, getDataReply_t _reply);

private:
    OnBoardProviderService * m_onBoardProviderService;
};

#endif // ONBOARDPROVIDERDBUSSERVICE_H
