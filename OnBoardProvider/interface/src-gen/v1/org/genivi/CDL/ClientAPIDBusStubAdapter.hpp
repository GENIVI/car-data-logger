/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.dbus 3.1.5.v201601121430.
* Used org.franca.core 0.9.1.201412191134.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
/**
 * description: CDL Client APIs for providing data to on-board components
 */
#ifndef V1_ORG_GENIVI_CDL_Client_API_DBUS_STUB_ADAPTER_HPP_
#define V1_ORG_GENIVI_CDL_Client_API_DBUS_STUB_ADAPTER_HPP_

#include <v1/org/genivi/CDL/ClientAPIStub.hpp>
#include "v1/org/genivi/CDL/ClientAPIDBusDeployment.hpp"        
#include <v1/org/genivi/CDL/ClientAPITypesDBusDeployment.hpp>        

#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif

#include <CommonAPI/DBus/DBusAddressTranslator.hpp>
#include <CommonAPI/DBus/DBusFactory.hpp>
#include <CommonAPI/DBus/DBusStubAdapterHelper.hpp>
#include <CommonAPI/DBus/DBusStubAdapter.hpp>
#include <CommonAPI/DBus/DBusDeployment.hpp>

#undef COMMONAPI_INTERNAL_COMPILATION

namespace v1 {
namespace org {
namespace genivi {
namespace CDL {

typedef CommonAPI::DBus::DBusStubAdapterHelper<ClientAPIStub> ClientAPIDBusStubAdapterHelper;

class ClientAPIDBusStubAdapterInternal
    : public virtual ClientAPIStubAdapter,
      public ClientAPIDBusStubAdapterHelper
{
public:
    ClientAPIDBusStubAdapterInternal(
            const CommonAPI::DBus::DBusAddress &_address,
            const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection> &_connection,
            const std::shared_ptr<CommonAPI::StubBase> &_stub);

    ~ClientAPIDBusStubAdapterInternal();

    virtual bool hasFreedesktopProperties();

    inline static const char* getInterface() {
        return ClientAPI::getInterface();
    }


    /**
     * description: notify data to client
     */
    void fireNotifyDataSelective(const std::shared_ptr<CommonAPI::ClientId> _client, const std::string &_signalName, const ::v1::org::genivi::CDL::ClientAPITypes::Types &_type, const std::string &_unit, const ::v1::org::genivi::CDL::ClientAPITypes::CDLValue &_value, const uint64_t &_timeStamp);
    void sendNotifyDataSelective(const std::string &_signalName, const ::v1::org::genivi::CDL::ClientAPITypes::Types &_type, const std::string &_unit, const ::v1::org::genivi::CDL::ClientAPITypes::CDLValue &_value, const uint64_t &_timeStamp, const std::shared_ptr<CommonAPI::ClientIdList> _receivers = nullptr);
    void subscribeFornotifyDataSelective(const std::shared_ptr<CommonAPI::ClientId> clientId, bool& success);
    void unsubscribeFromnotifyDataSelective(const std::shared_ptr<CommonAPI::ClientId> clientId);
    std::shared_ptr<CommonAPI::ClientIdList> const getSubscribersForNotifyDataSelective();


    const ClientAPIDBusStubAdapterHelper::StubDispatcherTable& getStubDispatcherTable();
    const CommonAPI::DBus::StubAttributeTable& getStubAttributeTable();

    void deactivateManagedInstances();
    

static CommonAPI::DBus::DBusGetAttributeStubDispatcher<
        ::v1::org::genivi::CDL::ClientAPIStub,
        CommonAPI::Version
        > getClientAPIInterfaceVersionStubDispatcher;



/**
 * description: register and authenticate client
 */

static CommonAPI::DBus::DBusMethodWithReplyStubDispatcher<
    ::v1::org::genivi::CDL::ClientAPIStub,
    std::tuple<std::string>,
    std::tuple<ClientAPITypes::Handle, ClientAPITypes::ResultCode>,
    std::tuple<CommonAPI::DBus::StringDeployment>,
    std::tuple<CommonAPI::EmptyDeployment, CommonAPI::EmptyDeployment>
    
    > registerClientStubDispatcher;
/**
 * description: set id list for listen. only specified data will notified to client
 */

static CommonAPI::DBus::DBusMethodWithReplyStubDispatcher<
    ::v1::org::genivi::CDL::ClientAPIStub,
    std::tuple<ClientAPITypes::Handle, std::vector<std::string>, ClientAPITypes::NotifyType>,
    std::tuple<ClientAPITypes::ResultCode>,
    std::tuple<CommonAPI::EmptyDeployment, CommonAPI::DBus::ArrayDeployment<CommonAPI::DBus::StringDeployment>, CommonAPI::EmptyDeployment>,
    std::tuple<CommonAPI::EmptyDeployment>
    
    > setListenDataStubDispatcher;
/**
 * description: get single data instantly
 */

static CommonAPI::DBus::DBusMethodWithReplyStubDispatcher<
    ::v1::org::genivi::CDL::ClientAPIStub,
    std::tuple<ClientAPITypes::Handle, std::string>,
    std::tuple<ClientAPITypes::ResultCode>,
    std::tuple<CommonAPI::EmptyDeployment, CommonAPI::DBus::StringDeployment>,
    std::tuple<CommonAPI::EmptyDeployment>
    
    > getDataStubDispatcher;


static CommonAPI::DBus::DBusMethodWithReplyAdapterDispatcher<
    ::v1::org::genivi::CDL::ClientAPIStub,
    ClientAPIStubAdapter,
    std::tuple<>,
    std::tuple<bool>
    > subscribeNotifyDataSelectiveStubDispatcher;

static CommonAPI::DBus::DBusMethodWithReplyAdapterDispatcher<
    ::v1::org::genivi::CDL::ClientAPIStub,
    ClientAPIStubAdapter,
 std::tuple<>,
    std::tuple<>
    > unsubscribeNotifyDataSelectiveStubDispatcher;


 protected:
    virtual const char* getMethodsDBusIntrospectionXmlData() const;

 private:
    ClientAPIDBusStubAdapterHelper::StubDispatcherTable stubDispatcherTable_;
    CommonAPI::DBus::StubAttributeTable stubAttributeTable_;
};

class ClientAPIDBusStubAdapter
    : public ClientAPIDBusStubAdapterInternal,
      public std::enable_shared_from_this<ClientAPIDBusStubAdapter> {
public:
    ClientAPIDBusStubAdapter(
    	const CommonAPI::DBus::DBusAddress &_address,
        const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection> &_connection,
        const std::shared_ptr<CommonAPI::StubBase> &_stub)
    	: CommonAPI::DBus::DBusStubAdapter(
    		_address, 
    		_connection,
            false),
          ClientAPIDBusStubAdapterInternal(
          	_address, 
          	_connection, 
          	_stub) { 
    }
};

} // namespace CDL
} // namespace genivi
} // namespace org
} // namespace v1

#endif // V1_ORG_GENIVI_CDL_Client_API_DBUS_STUB_ADAPTER_HPP_