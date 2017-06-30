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

#ifndef DBUSCLIENTTESTAPP_H
#define DBUSCLIENTTESTAPP_H

#include "org/genivi/CDL/ClientAPIProxy.hpp"

#include <QObject>
#include <QTimer>
#include <string>
#include <vector>

using namespace std;
using namespace v1::org::genivi::CDL;

class DBusClientTestApp2 : public QObject
{
    Q_OBJECT
public:
    DBusClientTestApp2();
    virtual ~DBusClientTestApp2();

private:
    virtual void createProxy();
    void subscribeEvents();
    void init();
    void onConnectionsStatusChanged(CommonAPI::AvailabilityStatus status);
    void onNotifyData(const string &_signalName, const ClientAPITypes::Types &_type, const string &_unit, const ClientAPITypes::CDLValue &_value, const uint64_t &_timeStamp);
    QString getDateTime(const uint64_t _utcTimeStamp);
    QString getCDLValue(const ClientAPITypes::CDLValue &value);

signals:
    void someipClientConnected();

public slots:
    void registeredClient();
    void requestVehicleData();

private:
    std::shared_ptr<ClientAPIProxy<>> m_proxy;
    ClientAPITypes::Handle m_handle;
    ClientAPITypes::NotifyType m_notiType;

    vector<string> m_dbusRequestedNameList;
    QTimer * m_timer;
};

#endif // DBUSCLIENTTESTAPP_H
