/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.someip 3.1.5.v201601121433.
* Used org.franca.core 0.9.1.201412191134.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
#include <v1/org/genivi/CDL/ClientAPISomeIPStubAdapter.hpp>
#include <v1/org/genivi/CDL/ClientAPI.hpp>

#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif

#include <CommonAPI/SomeIP/AddressTranslator.hpp>

#undef COMMONAPI_INTERNAL_COMPILATION

namespace v1 {
namespace org {
namespace genivi {
namespace CDL {

std::shared_ptr<CommonAPI::SomeIP::StubAdapter> createClientAPISomeIPStubAdapter(
                   const CommonAPI::SomeIP::Address &_address,
                   const std::shared_ptr<CommonAPI::SomeIP::ProxyConnection> &_connection,
                   const std::shared_ptr<CommonAPI::StubBase> &_stub) {
    return std::make_shared<ClientAPISomeIPStubAdapter>(_address, _connection, _stub);
}

INITIALIZER(registerClientAPISomeIPStubAdapter) {
    CommonAPI::SomeIP::AddressTranslator::get()->insert(
        "local:org.genivi.CDL.ClientAPI:org.genivi.CDL.ClientAPI.SomeIp",
         0x3e8, 0x44c, 1, 0);
    CommonAPI::SomeIP::Factory::get()->registerStubAdapterCreateMethod(
        ClientAPI::getInterface(), 
        &createClientAPISomeIPStubAdapter);
}

ClientAPISomeIPStubAdapterInternal::~ClientAPISomeIPStubAdapterInternal() {
    connection_->unregisterSubsciptionHandler(getSomeIpAddress(), 0x4e20);
    deactivateManagedInstances();
    ClientAPISomeIPStubAdapterHelper::deinit();
}

void ClientAPISomeIPStubAdapterInternal::deactivateManagedInstances() {

}

CommonAPI::SomeIP::GetAttributeStubDispatcher<
        ::v1::org::genivi::CDL::ClientAPIStub,
        CommonAPI::Version
        > ClientAPISomeIPStubAdapterInternal::getClientAPIInterfaceVersionStubDispatcher(&ClientAPIStub::getInterfaceVersion);

/**
 * description: register and authenticate client
 */
CommonAPI::SomeIP::MethodWithReplyStubDispatcher<
    ::v1::org::genivi::CDL::ClientAPIStub,
    std::tuple<std::string>,
    std::tuple<ClientAPITypes::Handle, ClientAPITypes::ResultCode>,
    std::tuple<CommonAPI::SomeIP::StringDeployment>,
    std::tuple<CommonAPI::EmptyDeployment, CommonAPI::SomeIP::EnumerationDeployment>
> ClientAPISomeIPStubAdapterInternal::registerClientStubDispatcher(
    &ClientAPIStub::registerClient, 
    std::make_tuple(static_cast<CommonAPI::SomeIP::StringDeployment*>(nullptr)),
    std::make_tuple(static_cast<CommonAPI::EmptyDeployment*>(nullptr), static_cast<CommonAPI::SomeIP::EnumerationDeployment*>(nullptr)));
/**
 * description: set id list for listen. only specified data will notified to client
 */
CommonAPI::SomeIP::MethodWithReplyStubDispatcher<
    ::v1::org::genivi::CDL::ClientAPIStub,
    std::tuple<ClientAPITypes::Handle, std::vector<std::string>, ClientAPITypes::NotifyType>,
    std::tuple<ClientAPITypes::ResultCode>,
    std::tuple<CommonAPI::EmptyDeployment, CommonAPI::SomeIP::ArrayDeployment<CommonAPI::SomeIP::StringDeployment>, CommonAPI::SomeIP::EnumerationDeployment>,
    std::tuple<CommonAPI::SomeIP::EnumerationDeployment>
> ClientAPISomeIPStubAdapterInternal::setListenDataStubDispatcher(
    &ClientAPIStub::setListenData, 
    std::make_tuple(static_cast<CommonAPI::EmptyDeployment*>(nullptr), static_cast<CommonAPI::SomeIP::ArrayDeployment<CommonAPI::SomeIP::StringDeployment>*>(nullptr), static_cast<CommonAPI::SomeIP::EnumerationDeployment*>(nullptr)),
    std::make_tuple(static_cast<CommonAPI::SomeIP::EnumerationDeployment*>(nullptr)));
/**
 * description: get single data instantly
 */
CommonAPI::SomeIP::MethodWithReplyStubDispatcher<
    ::v1::org::genivi::CDL::ClientAPIStub,
    std::tuple<ClientAPITypes::Handle, std::string>,
    std::tuple<ClientAPITypes::ResultCode>,
    std::tuple<CommonAPI::EmptyDeployment, CommonAPI::SomeIP::StringDeployment>,
    std::tuple<CommonAPI::SomeIP::EnumerationDeployment>
> ClientAPISomeIPStubAdapterInternal::getDataStubDispatcher(
    &ClientAPIStub::getData, 
    std::make_tuple(static_cast<CommonAPI::EmptyDeployment*>(nullptr), static_cast<CommonAPI::SomeIP::StringDeployment*>(nullptr)),
    std::make_tuple(static_cast<CommonAPI::SomeIP::EnumerationDeployment*>(nullptr)));


/**
 * description: notify data to client
 */
void ClientAPISomeIPStubAdapterInternal::fireNotifyDataSelective(const std::shared_ptr<CommonAPI::ClientId> _client, const std::string &_signalName, const ::v1::org::genivi::CDL::ClientAPITypes::Types &_type, const std::string &_unit, const ::v1::org::genivi::CDL::ClientAPITypes::CDLValue &_value, const uint64_t &_timeStamp) {
    std::shared_ptr<CommonAPI::SomeIP::ClientId> client = std::dynamic_pointer_cast<CommonAPI::SomeIP::ClientId, CommonAPI::ClientId>(_client);
CommonAPI::Deployable<std::string, CommonAPI::SomeIP::StringDeployment> deployed_signalName(_signalName, static_cast<CommonAPI::SomeIP::StringDeployment*>(nullptr));
CommonAPI::Deployable<ClientAPITypes::Types, CommonAPI::SomeIP::EnumerationDeployment> deployed_type(_type, static_cast<CommonAPI::SomeIP::EnumerationDeployment*>(nullptr));
CommonAPI::Deployable<std::string, CommonAPI::SomeIP::StringDeployment> deployed_unit(_unit, static_cast<CommonAPI::SomeIP::StringDeployment*>(nullptr));
CommonAPI::Deployable<ClientAPITypes::CDLValue, ::v1::org::genivi::CDL::ClientAPITypes_::CDLValueDeployment_t> deployed_value(_value, static_cast<::v1::org::genivi::CDL::ClientAPITypes_::CDLValueDeployment_t*>(nullptr));
  if (client) {
      CommonAPI::SomeIP::StubEventHelper<CommonAPI::SomeIP::SerializableArguments< CommonAPI::Deployable< std::string, CommonAPI::SomeIP::StringDeployment > 
      ,  CommonAPI::Deployable< ::v1::org::genivi::CDL::ClientAPITypes::Types, CommonAPI::SomeIP::EnumerationDeployment > 
      ,  CommonAPI::Deployable< std::string, CommonAPI::SomeIP::StringDeployment > 
      ,  CommonAPI::Deployable< ::v1::org::genivi::CDL::ClientAPITypes::CDLValue, ::v1::org::genivi::CDL::ClientAPITypes_::CDLValueDeployment_t > 
      ,  uint64_t
      >>
        ::sendEvent(
            client->getClientId(),
            *this,
            CommonAPI::SomeIP::event_id_t(0x4e21),
             deployed_signalName 
            ,  deployed_type 
            ,  deployed_unit 
            ,  deployed_value 
            , _timeStamp
        );
   }
}

void ClientAPISomeIPStubAdapterInternal::sendNotifyDataSelective(const std::string &_signalName, const ::v1::org::genivi::CDL::ClientAPITypes::Types &_type, const std::string &_unit, const ::v1::org::genivi::CDL::ClientAPITypes::CDLValue &_value, const uint64_t &_timeStamp, const std::shared_ptr<CommonAPI::ClientIdList> _receivers) {
    std::shared_ptr<CommonAPI::ClientIdList> actualReceiverList;
    actualReceiverList = _receivers;

    if(_receivers == NULL)
        actualReceiverList = subscribersForNotifyDataSelective_;

    for (auto clientIdIterator = actualReceiverList->cbegin();
               clientIdIterator != actualReceiverList->cend();
               clientIdIterator++) {
        if(_receivers == NULL || subscribersForNotifyDataSelective_->find(*clientIdIterator) != subscribersForNotifyDataSelective_->end()) {
            fireNotifyDataSelective(*clientIdIterator, _signalName, _type, _unit, _value, _timeStamp);
        }
    }
}

void ClientAPISomeIPStubAdapterInternal::subscribeFornotifyDataSelective(const std::shared_ptr<CommonAPI::ClientId> clientId, bool& success) {
    std::lock_guard<std::mutex> itsLock(NotifyDataSelectiveEventMutex_);
    bool ok = ClientAPISomeIPStubAdapterHelper::stub_->onNotifyDataSelectiveSubscriptionRequested(clientId);
    if (ok) {
        subscribersForNotifyDataSelective_->insert(clientId);
        ClientAPISomeIPStubAdapterHelper::stub_->onNotifyDataSelectiveSubscriptionChanged(clientId, CommonAPI::SelectiveBroadcastSubscriptionEvent::SUBSCRIBED);
        success = true;
    } else {
        success = false;
    }
}

void ClientAPISomeIPStubAdapterInternal::unsubscribeFromnotifyDataSelective(const std::shared_ptr<CommonAPI::ClientId> clientId) {
    std::lock_guard<std::mutex> itsLock(NotifyDataSelectiveEventMutex_);
    subscribersForNotifyDataSelective_->erase(clientId);
    ClientAPISomeIPStubAdapterHelper::stub_->onNotifyDataSelectiveSubscriptionChanged(clientId, CommonAPI::SelectiveBroadcastSubscriptionEvent::UNSUBSCRIBED);
}

std::shared_ptr<CommonAPI::ClientIdList> const ClientAPISomeIPStubAdapterInternal::getSubscribersForNotifyDataSelective() {
    return subscribersForNotifyDataSelective_;
}

bool ClientAPISomeIPStubAdapterInternal::NotifyDataSelectiveEventHandler(CommonAPI::SomeIP::client_id_t _client, bool subscribe) {
    std::shared_ptr<CommonAPI::SomeIP::ClientId> clientId = std::make_shared<CommonAPI::SomeIP::ClientId>(CommonAPI::SomeIP::ClientId(_client));
    bool result = true;
    if (subscribe) {
        subscribeFornotifyDataSelective(clientId, result);
    } else {
        unsubscribeFromnotifyDataSelective(clientId);
    }
    return result;
}


const ClientAPISomeIPStubAdapterHelper::StubDispatcherTable& ClientAPISomeIPStubAdapterInternal::getStubDispatcherTable() {
    return stubDispatcherTable_;
}

const CommonAPI::SomeIP::StubAttributeTable& ClientAPISomeIPStubAdapterInternal::getStubAttributeTable() {
    return stubAttributeTable_;
}


ClientAPISomeIPStubAdapterInternal::ClientAPISomeIPStubAdapterInternal(
        const CommonAPI::SomeIP::Address &_address,
        const std::shared_ptr<CommonAPI::SomeIP::ProxyConnection> &_connection,
        const std::shared_ptr<CommonAPI::StubBase> &_stub):
        CommonAPI::SomeIP::StubAdapter(_address, _connection),
        ClientAPISomeIPStubAdapterHelper(
            _address, 
            _connection,
            std::dynamic_pointer_cast<ClientAPIStub>(_stub)),
        stubDispatcherTable_({
            /**
             * description: register and authenticate client
             */
            { { CommonAPI::SomeIP::method_id_t(0x2710) }, &org::genivi::CDL::ClientAPISomeIPStubAdapterInternal::registerClientStubDispatcher },
            /**
             * description: set id list for listen. only specified data will notified to client
             */
            { { CommonAPI::SomeIP::method_id_t(0x2711) }, &org::genivi::CDL::ClientAPISomeIPStubAdapterInternal::setListenDataStubDispatcher },
            /**
             * description: get single data instantly
             */
            { { CommonAPI::SomeIP::method_id_t(0x2712) }, &org::genivi::CDL::ClientAPISomeIPStubAdapterInternal::getDataStubDispatcher }
        }),
        stubAttributeTable_(
        ) {
    subscribersForNotifyDataSelective_ = std::make_shared<CommonAPI::ClientIdList>();
    CommonAPI::SomeIP::SubsciptionHandler_t NotifyDataSelectiveEventSubscribeHandler =
        std::bind(&ClientAPISomeIPStubAdapterInternal::NotifyDataSelectiveEventHandler,
        this, std::placeholders::_1, std::placeholders::_2);

    connection_->registerSubsciptionHandler(getSomeIpAddress(), 0x4e20, NotifyDataSelectiveEventSubscribeHandler);
    
    // Provided events/fields
    {
        std::set<CommonAPI::SomeIP::eventgroup_id_t> itsEventGroups;
        itsEventGroups.insert(CommonAPI::SomeIP::eventgroup_id_t(0x4e20));
        registerEvent(CommonAPI::SomeIP::event_id_t(0x4e21), itsEventGroups, false);
    }

}

} // namespace CDL
} // namespace genivi
} // namespace org
} // namespace v1