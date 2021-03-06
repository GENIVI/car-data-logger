/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.core 3.1.10.v201611111521.
* Used org.franca.core 0.9.1.201412191134.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
#include <v1/com/ivis/DATCManager/DATCManagerStubDefault.hpp>
#include <assert.h>

namespace v1 {
namespace com {
namespace ivis {
namespace DATCManager {

DATCManagerStubDefault::DATCManagerStubDefault():
        remoteEventHandler_(this),
        interfaceVersion_(DATCManager::getInterfaceVersion()) {
}

const CommonAPI::Version& DATCManagerStubDefault::getInterfaceVersion(std::shared_ptr<CommonAPI::ClientId> _client) {
    (void)_client;
    return interfaceVersion_;
}

DATCManagerStubRemoteEvent* DATCManagerStubDefault::initStubAdapter(const std::shared_ptr< DATCManagerStubAdapter> &_adapter) {
    CommonAPI::Stub<DATCManagerStubAdapter, DATCManagerStubRemoteEvent>::stubAdapter_ = _adapter;
    return &remoteEventHandler_;
}

const ::v1::com::ivis::DATCManager::DATCManagerTypes::ETemperatureMode& DATCManagerStubDefault::getTemperatureModeAttribute() {
    return temperatureModeAttributeValue_;
}

const ::v1::com::ivis::DATCManager::DATCManagerTypes::ETemperatureMode& DATCManagerStubDefault::getTemperatureModeAttribute(const std::shared_ptr<CommonAPI::ClientId> _client) {
    (void)_client;
    return getTemperatureModeAttribute();
}

void DATCManagerStubDefault::setTemperatureModeAttribute(::v1::com::ivis::DATCManager::DATCManagerTypes::ETemperatureMode _value) {
    const bool valueChanged = trySetTemperatureModeAttribute(std::move(_value));
    if (valueChanged) {
        fireTemperatureModeAttributeChanged(temperatureModeAttributeValue_);
    }
}

bool DATCManagerStubDefault::trySetTemperatureModeAttribute(::v1::com::ivis::DATCManager::DATCManagerTypes::ETemperatureMode _value) {
    if (!validateTemperatureModeAttributeRequestedValue(_value))
        return false;

    const bool valueChanged = (temperatureModeAttributeValue_ != _value);
    temperatureModeAttributeValue_ = std::move(_value);
    return valueChanged;
}

bool DATCManagerStubDefault::validateTemperatureModeAttributeRequestedValue(const ::v1::com::ivis::DATCManager::DATCManagerTypes::ETemperatureMode &_value) {
    (void)_value;
    return _value.validate();
}

void DATCManagerStubDefault::setTemperatureModeAttribute(const std::shared_ptr<CommonAPI::ClientId> _client, ::v1::com::ivis::DATCManager::DATCManagerTypes::ETemperatureMode _value) {
    (void)_client;
    setTemperatureModeAttribute(_value);
}

void DATCManagerStubDefault::onRemoteTemperatureModeAttributeChanged() {
    // No operation in default
}

void DATCManagerStubDefault::RemoteEventHandler::onRemoteTemperatureModeAttributeChanged() {
    assert(defaultStub_ !=NULL);
    defaultStub_->onRemoteTemperatureModeAttributeChanged();
}

bool DATCManagerStubDefault::RemoteEventHandler::onRemoteSetTemperatureModeAttribute(::v1::com::ivis::DATCManager::DATCManagerTypes::ETemperatureMode _value) {
    assert(defaultStub_ !=NULL);
    return defaultStub_->trySetTemperatureModeAttribute(std::move(_value));
}

bool DATCManagerStubDefault::RemoteEventHandler::onRemoteSetTemperatureModeAttribute(const std::shared_ptr<CommonAPI::ClientId> _client, ::v1::com::ivis::DATCManager::DATCManagerTypes::ETemperatureMode _value) {
    (void)_client;
    return onRemoteSetTemperatureModeAttribute(_value);
}

const bool& DATCManagerStubDefault::getDualModeAttribute() {
    return dualModeAttributeValue_;
}

const bool& DATCManagerStubDefault::getDualModeAttribute(const std::shared_ptr<CommonAPI::ClientId> _client) {
    (void)_client;
    return getDualModeAttribute();
}

void DATCManagerStubDefault::setDualModeAttribute(bool _value) {
    const bool valueChanged = trySetDualModeAttribute(std::move(_value));
    if (valueChanged) {
        fireDualModeAttributeChanged(dualModeAttributeValue_);
    }
}

bool DATCManagerStubDefault::trySetDualModeAttribute(bool _value) {
    if (!validateDualModeAttributeRequestedValue(_value))
        return false;

    const bool valueChanged = (dualModeAttributeValue_ != _value);
    dualModeAttributeValue_ = std::move(_value);
    return valueChanged;
}

bool DATCManagerStubDefault::validateDualModeAttributeRequestedValue(const bool &_value) {
    (void)_value;
    return true;
}

void DATCManagerStubDefault::setDualModeAttribute(const std::shared_ptr<CommonAPI::ClientId> _client, bool _value) {
    (void)_client;
    setDualModeAttribute(_value);
}

void DATCManagerStubDefault::onRemoteDualModeAttributeChanged() {
    // No operation in default
}

void DATCManagerStubDefault::RemoteEventHandler::onRemoteDualModeAttributeChanged() {
    assert(defaultStub_ !=NULL);
    defaultStub_->onRemoteDualModeAttributeChanged();
}

bool DATCManagerStubDefault::RemoteEventHandler::onRemoteSetDualModeAttribute(bool _value) {
    assert(defaultStub_ !=NULL);
    return defaultStub_->trySetDualModeAttribute(std::move(_value));
}

bool DATCManagerStubDefault::RemoteEventHandler::onRemoteSetDualModeAttribute(const std::shared_ptr<CommonAPI::ClientId> _client, bool _value) {
    (void)_client;
    return onRemoteSetDualModeAttribute(_value);
}

const bool& DATCManagerStubDefault::getAutoModeAttribute() {
    return autoModeAttributeValue_;
}

const bool& DATCManagerStubDefault::getAutoModeAttribute(const std::shared_ptr<CommonAPI::ClientId> _client) {
    (void)_client;
    return getAutoModeAttribute();
}

void DATCManagerStubDefault::setAutoModeAttribute(bool _value) {
    const bool valueChanged = trySetAutoModeAttribute(std::move(_value));
    if (valueChanged) {
        fireAutoModeAttributeChanged(autoModeAttributeValue_);
    }
}

bool DATCManagerStubDefault::trySetAutoModeAttribute(bool _value) {
    if (!validateAutoModeAttributeRequestedValue(_value))
        return false;

    const bool valueChanged = (autoModeAttributeValue_ != _value);
    autoModeAttributeValue_ = std::move(_value);
    return valueChanged;
}

bool DATCManagerStubDefault::validateAutoModeAttributeRequestedValue(const bool &_value) {
    (void)_value;
    return true;
}

void DATCManagerStubDefault::setAutoModeAttribute(const std::shared_ptr<CommonAPI::ClientId> _client, bool _value) {
    (void)_client;
    setAutoModeAttribute(_value);
}

void DATCManagerStubDefault::onRemoteAutoModeAttributeChanged() {
    // No operation in default
}

void DATCManagerStubDefault::RemoteEventHandler::onRemoteAutoModeAttributeChanged() {
    assert(defaultStub_ !=NULL);
    defaultStub_->onRemoteAutoModeAttributeChanged();
}

bool DATCManagerStubDefault::RemoteEventHandler::onRemoteSetAutoModeAttribute(bool _value) {
    assert(defaultStub_ !=NULL);
    return defaultStub_->trySetAutoModeAttribute(std::move(_value));
}

bool DATCManagerStubDefault::RemoteEventHandler::onRemoteSetAutoModeAttribute(const std::shared_ptr<CommonAPI::ClientId> _client, bool _value) {
    (void)_client;
    return onRemoteSetAutoModeAttribute(_value);
}

const bool& DATCManagerStubDefault::getAirConditionerRunAttribute() {
    return airConditionerRunAttributeValue_;
}

const bool& DATCManagerStubDefault::getAirConditionerRunAttribute(const std::shared_ptr<CommonAPI::ClientId> _client) {
    (void)_client;
    return getAirConditionerRunAttribute();
}

void DATCManagerStubDefault::setAirConditionerRunAttribute(bool _value) {
    const bool valueChanged = trySetAirConditionerRunAttribute(std::move(_value));
    if (valueChanged) {
        fireAirConditionerRunAttributeChanged(airConditionerRunAttributeValue_);
    }
}

bool DATCManagerStubDefault::trySetAirConditionerRunAttribute(bool _value) {
    if (!validateAirConditionerRunAttributeRequestedValue(_value))
        return false;

    const bool valueChanged = (airConditionerRunAttributeValue_ != _value);
    airConditionerRunAttributeValue_ = std::move(_value);
    return valueChanged;
}

bool DATCManagerStubDefault::validateAirConditionerRunAttributeRequestedValue(const bool &_value) {
    (void)_value;
    return true;
}

void DATCManagerStubDefault::setAirConditionerRunAttribute(const std::shared_ptr<CommonAPI::ClientId> _client, bool _value) {
    (void)_client;
    setAirConditionerRunAttribute(_value);
}

void DATCManagerStubDefault::onRemoteAirConditionerRunAttributeChanged() {
    // No operation in default
}

void DATCManagerStubDefault::RemoteEventHandler::onRemoteAirConditionerRunAttributeChanged() {
    assert(defaultStub_ !=NULL);
    defaultStub_->onRemoteAirConditionerRunAttributeChanged();
}

bool DATCManagerStubDefault::RemoteEventHandler::onRemoteSetAirConditionerRunAttribute(bool _value) {
    assert(defaultStub_ !=NULL);
    return defaultStub_->trySetAirConditionerRunAttribute(std::move(_value));
}

bool DATCManagerStubDefault::RemoteEventHandler::onRemoteSetAirConditionerRunAttribute(const std::shared_ptr<CommonAPI::ClientId> _client, bool _value) {
    (void)_client;
    return onRemoteSetAirConditionerRunAttribute(_value);
}

const bool& DATCManagerStubDefault::getHeaterRunAttribute() {
    return heaterRunAttributeValue_;
}

const bool& DATCManagerStubDefault::getHeaterRunAttribute(const std::shared_ptr<CommonAPI::ClientId> _client) {
    (void)_client;
    return getHeaterRunAttribute();
}

void DATCManagerStubDefault::setHeaterRunAttribute(bool _value) {
    const bool valueChanged = trySetHeaterRunAttribute(std::move(_value));
    if (valueChanged) {
        fireHeaterRunAttributeChanged(heaterRunAttributeValue_);
    }
}

bool DATCManagerStubDefault::trySetHeaterRunAttribute(bool _value) {
    if (!validateHeaterRunAttributeRequestedValue(_value))
        return false;

    const bool valueChanged = (heaterRunAttributeValue_ != _value);
    heaterRunAttributeValue_ = std::move(_value);
    return valueChanged;
}

bool DATCManagerStubDefault::validateHeaterRunAttributeRequestedValue(const bool &_value) {
    (void)_value;
    return true;
}

void DATCManagerStubDefault::setHeaterRunAttribute(const std::shared_ptr<CommonAPI::ClientId> _client, bool _value) {
    (void)_client;
    setHeaterRunAttribute(_value);
}

void DATCManagerStubDefault::onRemoteHeaterRunAttributeChanged() {
    // No operation in default
}

void DATCManagerStubDefault::RemoteEventHandler::onRemoteHeaterRunAttributeChanged() {
    assert(defaultStub_ !=NULL);
    defaultStub_->onRemoteHeaterRunAttributeChanged();
}

bool DATCManagerStubDefault::RemoteEventHandler::onRemoteSetHeaterRunAttribute(bool _value) {
    assert(defaultStub_ !=NULL);
    return defaultStub_->trySetHeaterRunAttribute(std::move(_value));
}

bool DATCManagerStubDefault::RemoteEventHandler::onRemoteSetHeaterRunAttribute(const std::shared_ptr<CommonAPI::ClientId> _client, bool _value) {
    (void)_client;
    return onRemoteSetHeaterRunAttribute(_value);
}

const double& DATCManagerStubDefault::getInteriorTemperautreAttribute() {
    return interiorTemperautreAttributeValue_;
}

const double& DATCManagerStubDefault::getInteriorTemperautreAttribute(const std::shared_ptr<CommonAPI::ClientId> _client) {
    (void)_client;
    return getInteriorTemperautreAttribute();
}

void DATCManagerStubDefault::setInteriorTemperautreAttribute(double _value) {
    const bool valueChanged = trySetInteriorTemperautreAttribute(std::move(_value));
    if (valueChanged) {
        fireInteriorTemperautreAttributeChanged(interiorTemperautreAttributeValue_);
    }
}

bool DATCManagerStubDefault::trySetInteriorTemperautreAttribute(double _value) {
    if (!validateInteriorTemperautreAttributeRequestedValue(_value))
        return false;

    const bool valueChanged = (interiorTemperautreAttributeValue_ != _value);
    interiorTemperautreAttributeValue_ = std::move(_value);
    return valueChanged;
}

bool DATCManagerStubDefault::validateInteriorTemperautreAttributeRequestedValue(const double &_value) {
    (void)_value;
    return true;
}


const double& DATCManagerStubDefault::getExteriorTemperatureAttribute() {
    return exteriorTemperatureAttributeValue_;
}

const double& DATCManagerStubDefault::getExteriorTemperatureAttribute(const std::shared_ptr<CommonAPI::ClientId> _client) {
    (void)_client;
    return getExteriorTemperatureAttribute();
}

void DATCManagerStubDefault::setExteriorTemperatureAttribute(double _value) {
    const bool valueChanged = trySetExteriorTemperatureAttribute(std::move(_value));
    if (valueChanged) {
        fireExteriorTemperatureAttributeChanged(exteriorTemperatureAttributeValue_);
    }
}

bool DATCManagerStubDefault::trySetExteriorTemperatureAttribute(double _value) {
    if (!validateExteriorTemperatureAttributeRequestedValue(_value))
        return false;

    const bool valueChanged = (exteriorTemperatureAttributeValue_ != _value);
    exteriorTemperatureAttributeValue_ = std::move(_value);
    return valueChanged;
}

bool DATCManagerStubDefault::validateExteriorTemperatureAttributeRequestedValue(const double &_value) {
    (void)_value;
    return true;
}


const ::v1::com::ivis::DATCManager::DATCManagerTypes::TargetTemperatures& DATCManagerStubDefault::getTargetTemperaturesAttribute() {
    return targetTemperaturesAttributeValue_;
}

const ::v1::com::ivis::DATCManager::DATCManagerTypes::TargetTemperatures& DATCManagerStubDefault::getTargetTemperaturesAttribute(const std::shared_ptr<CommonAPI::ClientId> _client) {
    (void)_client;
    return getTargetTemperaturesAttribute();
}

void DATCManagerStubDefault::setTargetTemperaturesAttribute(::v1::com::ivis::DATCManager::DATCManagerTypes::TargetTemperatures _value) {
    const bool valueChanged = trySetTargetTemperaturesAttribute(std::move(_value));
    if (valueChanged) {
        fireTargetTemperaturesAttributeChanged(targetTemperaturesAttributeValue_);
    }
}

bool DATCManagerStubDefault::trySetTargetTemperaturesAttribute(::v1::com::ivis::DATCManager::DATCManagerTypes::TargetTemperatures _value) {
    if (!validateTargetTemperaturesAttributeRequestedValue(_value))
        return false;

    const bool valueChanged = (targetTemperaturesAttributeValue_ != _value);
    targetTemperaturesAttributeValue_ = std::move(_value);
    return valueChanged;
}

bool DATCManagerStubDefault::validateTargetTemperaturesAttributeRequestedValue(const ::v1::com::ivis::DATCManager::DATCManagerTypes::TargetTemperatures &_value) {
    (void)_value;
    return true;
}

void DATCManagerStubDefault::setTargetTemperaturesAttribute(const std::shared_ptr<CommonAPI::ClientId> _client, ::v1::com::ivis::DATCManager::DATCManagerTypes::TargetTemperatures _value) {
    (void)_client;
    setTargetTemperaturesAttribute(_value);
}

void DATCManagerStubDefault::onRemoteTargetTemperaturesAttributeChanged() {
    // No operation in default
}

void DATCManagerStubDefault::RemoteEventHandler::onRemoteTargetTemperaturesAttributeChanged() {
    assert(defaultStub_ !=NULL);
    defaultStub_->onRemoteTargetTemperaturesAttributeChanged();
}

bool DATCManagerStubDefault::RemoteEventHandler::onRemoteSetTargetTemperaturesAttribute(::v1::com::ivis::DATCManager::DATCManagerTypes::TargetTemperatures _value) {
    assert(defaultStub_ !=NULL);
    return defaultStub_->trySetTargetTemperaturesAttribute(std::move(_value));
}

bool DATCManagerStubDefault::RemoteEventHandler::onRemoteSetTargetTemperaturesAttribute(const std::shared_ptr<CommonAPI::ClientId> _client, ::v1::com::ivis::DATCManager::DATCManagerTypes::TargetTemperatures _value) {
    (void)_client;
    return onRemoteSetTargetTemperaturesAttribute(_value);
}

const ::v1::com::ivis::DATCManager::DATCManagerTypes::FanDirections& DATCManagerStubDefault::getFanDirectionsAttribute() {
    return fanDirectionsAttributeValue_;
}

const ::v1::com::ivis::DATCManager::DATCManagerTypes::FanDirections& DATCManagerStubDefault::getFanDirectionsAttribute(const std::shared_ptr<CommonAPI::ClientId> _client) {
    (void)_client;
    return getFanDirectionsAttribute();
}

void DATCManagerStubDefault::setFanDirectionsAttribute(::v1::com::ivis::DATCManager::DATCManagerTypes::FanDirections _value) {
    const bool valueChanged = trySetFanDirectionsAttribute(std::move(_value));
    if (valueChanged) {
        fireFanDirectionsAttributeChanged(fanDirectionsAttributeValue_);
    }
}

bool DATCManagerStubDefault::trySetFanDirectionsAttribute(::v1::com::ivis::DATCManager::DATCManagerTypes::FanDirections _value) {
    if (!validateFanDirectionsAttributeRequestedValue(_value))
        return false;

    const bool valueChanged = (fanDirectionsAttributeValue_ != _value);
    fanDirectionsAttributeValue_ = std::move(_value);
    return valueChanged;
}

bool DATCManagerStubDefault::validateFanDirectionsAttributeRequestedValue(const ::v1::com::ivis::DATCManager::DATCManagerTypes::FanDirections &_value) {
    (void)_value;
    return true;
}

void DATCManagerStubDefault::setFanDirectionsAttribute(const std::shared_ptr<CommonAPI::ClientId> _client, ::v1::com::ivis::DATCManager::DATCManagerTypes::FanDirections _value) {
    (void)_client;
    setFanDirectionsAttribute(_value);
}

void DATCManagerStubDefault::onRemoteFanDirectionsAttributeChanged() {
    // No operation in default
}

void DATCManagerStubDefault::RemoteEventHandler::onRemoteFanDirectionsAttributeChanged() {
    assert(defaultStub_ !=NULL);
    defaultStub_->onRemoteFanDirectionsAttributeChanged();
}

bool DATCManagerStubDefault::RemoteEventHandler::onRemoteSetFanDirectionsAttribute(::v1::com::ivis::DATCManager::DATCManagerTypes::FanDirections _value) {
    assert(defaultStub_ !=NULL);
    return defaultStub_->trySetFanDirectionsAttribute(std::move(_value));
}

bool DATCManagerStubDefault::RemoteEventHandler::onRemoteSetFanDirectionsAttribute(const std::shared_ptr<CommonAPI::ClientId> _client, ::v1::com::ivis::DATCManager::DATCManagerTypes::FanDirections _value) {
    (void)_client;
    return onRemoteSetFanDirectionsAttribute(_value);
}

const ::v1::com::ivis::DATCManager::DATCManagerTypes::FanSpeeds& DATCManagerStubDefault::getFanSpeedsAttribute() {
    return fanSpeedsAttributeValue_;
}

const ::v1::com::ivis::DATCManager::DATCManagerTypes::FanSpeeds& DATCManagerStubDefault::getFanSpeedsAttribute(const std::shared_ptr<CommonAPI::ClientId> _client) {
    (void)_client;
    return getFanSpeedsAttribute();
}

void DATCManagerStubDefault::setFanSpeedsAttribute(::v1::com::ivis::DATCManager::DATCManagerTypes::FanSpeeds _value) {
    const bool valueChanged = trySetFanSpeedsAttribute(std::move(_value));
    if (valueChanged) {
        fireFanSpeedsAttributeChanged(fanSpeedsAttributeValue_);
    }
}

bool DATCManagerStubDefault::trySetFanSpeedsAttribute(::v1::com::ivis::DATCManager::DATCManagerTypes::FanSpeeds _value) {
    if (!validateFanSpeedsAttributeRequestedValue(_value))
        return false;

    const bool valueChanged = (fanSpeedsAttributeValue_ != _value);
    fanSpeedsAttributeValue_ = std::move(_value);
    return valueChanged;
}

bool DATCManagerStubDefault::validateFanSpeedsAttributeRequestedValue(const ::v1::com::ivis::DATCManager::DATCManagerTypes::FanSpeeds &_value) {
    (void)_value;
    return true;
}

void DATCManagerStubDefault::setFanSpeedsAttribute(const std::shared_ptr<CommonAPI::ClientId> _client, ::v1::com::ivis::DATCManager::DATCManagerTypes::FanSpeeds _value) {
    (void)_client;
    setFanSpeedsAttribute(_value);
}

void DATCManagerStubDefault::onRemoteFanSpeedsAttributeChanged() {
    // No operation in default
}

void DATCManagerStubDefault::RemoteEventHandler::onRemoteFanSpeedsAttributeChanged() {
    assert(defaultStub_ !=NULL);
    defaultStub_->onRemoteFanSpeedsAttributeChanged();
}

bool DATCManagerStubDefault::RemoteEventHandler::onRemoteSetFanSpeedsAttribute(::v1::com::ivis::DATCManager::DATCManagerTypes::FanSpeeds _value) {
    assert(defaultStub_ !=NULL);
    return defaultStub_->trySetFanSpeedsAttribute(std::move(_value));
}

bool DATCManagerStubDefault::RemoteEventHandler::onRemoteSetFanSpeedsAttribute(const std::shared_ptr<CommonAPI::ClientId> _client, ::v1::com::ivis::DATCManager::DATCManagerTypes::FanSpeeds _value) {
    (void)_client;
    return onRemoteSetFanSpeedsAttribute(_value);
}

const ::v1::com::ivis::DATCManager::DATCManagerTypes::Defrosts& DATCManagerStubDefault::getDefrostsAttribute() {
    return defrostsAttributeValue_;
}

const ::v1::com::ivis::DATCManager::DATCManagerTypes::Defrosts& DATCManagerStubDefault::getDefrostsAttribute(const std::shared_ptr<CommonAPI::ClientId> _client) {
    (void)_client;
    return getDefrostsAttribute();
}

void DATCManagerStubDefault::setDefrostsAttribute(::v1::com::ivis::DATCManager::DATCManagerTypes::Defrosts _value) {
    const bool valueChanged = trySetDefrostsAttribute(std::move(_value));
    if (valueChanged) {
        fireDefrostsAttributeChanged(defrostsAttributeValue_);
    }
}

bool DATCManagerStubDefault::trySetDefrostsAttribute(::v1::com::ivis::DATCManager::DATCManagerTypes::Defrosts _value) {
    if (!validateDefrostsAttributeRequestedValue(_value))
        return false;

    const bool valueChanged = (defrostsAttributeValue_ != _value);
    defrostsAttributeValue_ = std::move(_value);
    return valueChanged;
}

bool DATCManagerStubDefault::validateDefrostsAttributeRequestedValue(const ::v1::com::ivis::DATCManager::DATCManagerTypes::Defrosts &_value) {
    (void)_value;
    return true;
}

void DATCManagerStubDefault::setDefrostsAttribute(const std::shared_ptr<CommonAPI::ClientId> _client, ::v1::com::ivis::DATCManager::DATCManagerTypes::Defrosts _value) {
    (void)_client;
    setDefrostsAttribute(_value);
}

void DATCManagerStubDefault::onRemoteDefrostsAttributeChanged() {
    // No operation in default
}

void DATCManagerStubDefault::RemoteEventHandler::onRemoteDefrostsAttributeChanged() {
    assert(defaultStub_ !=NULL);
    defaultStub_->onRemoteDefrostsAttributeChanged();
}

bool DATCManagerStubDefault::RemoteEventHandler::onRemoteSetDefrostsAttribute(::v1::com::ivis::DATCManager::DATCManagerTypes::Defrosts _value) {
    assert(defaultStub_ !=NULL);
    return defaultStub_->trySetDefrostsAttribute(std::move(_value));
}

bool DATCManagerStubDefault::RemoteEventHandler::onRemoteSetDefrostsAttribute(const std::shared_ptr<CommonAPI::ClientId> _client, ::v1::com::ivis::DATCManager::DATCManagerTypes::Defrosts _value) {
    (void)_client;
    return onRemoteSetDefrostsAttribute(_value);
}

const bool& DATCManagerStubDefault::getAirRecirculationAttribute() {
    return airRecirculationAttributeValue_;
}

const bool& DATCManagerStubDefault::getAirRecirculationAttribute(const std::shared_ptr<CommonAPI::ClientId> _client) {
    (void)_client;
    return getAirRecirculationAttribute();
}

void DATCManagerStubDefault::setAirRecirculationAttribute(bool _value) {
    const bool valueChanged = trySetAirRecirculationAttribute(std::move(_value));
    if (valueChanged) {
        fireAirRecirculationAttributeChanged(airRecirculationAttributeValue_);
    }
}

bool DATCManagerStubDefault::trySetAirRecirculationAttribute(bool _value) {
    if (!validateAirRecirculationAttributeRequestedValue(_value))
        return false;

    const bool valueChanged = (airRecirculationAttributeValue_ != _value);
    airRecirculationAttributeValue_ = std::move(_value);
    return valueChanged;
}

bool DATCManagerStubDefault::validateAirRecirculationAttributeRequestedValue(const bool &_value) {
    (void)_value;
    return true;
}

void DATCManagerStubDefault::setAirRecirculationAttribute(const std::shared_ptr<CommonAPI::ClientId> _client, bool _value) {
    (void)_client;
    setAirRecirculationAttribute(_value);
}

void DATCManagerStubDefault::onRemoteAirRecirculationAttributeChanged() {
    // No operation in default
}

void DATCManagerStubDefault::RemoteEventHandler::onRemoteAirRecirculationAttributeChanged() {
    assert(defaultStub_ !=NULL);
    defaultStub_->onRemoteAirRecirculationAttributeChanged();
}

bool DATCManagerStubDefault::RemoteEventHandler::onRemoteSetAirRecirculationAttribute(bool _value) {
    assert(defaultStub_ !=NULL);
    return defaultStub_->trySetAirRecirculationAttribute(std::move(_value));
}

bool DATCManagerStubDefault::RemoteEventHandler::onRemoteSetAirRecirculationAttribute(const std::shared_ptr<CommonAPI::ClientId> _client, bool _value) {
    (void)_client;
    return onRemoteSetAirRecirculationAttribute(_value);
}

const bool& DATCManagerStubDefault::getSteeringWheelHeaterAttribute() {
    return steeringWheelHeaterAttributeValue_;
}

const bool& DATCManagerStubDefault::getSteeringWheelHeaterAttribute(const std::shared_ptr<CommonAPI::ClientId> _client) {
    (void)_client;
    return getSteeringWheelHeaterAttribute();
}

void DATCManagerStubDefault::setSteeringWheelHeaterAttribute(bool _value) {
    const bool valueChanged = trySetSteeringWheelHeaterAttribute(std::move(_value));
    if (valueChanged) {
        fireSteeringWheelHeaterAttributeChanged(steeringWheelHeaterAttributeValue_);
    }
}

bool DATCManagerStubDefault::trySetSteeringWheelHeaterAttribute(bool _value) {
    if (!validateSteeringWheelHeaterAttributeRequestedValue(_value))
        return false;

    const bool valueChanged = (steeringWheelHeaterAttributeValue_ != _value);
    steeringWheelHeaterAttributeValue_ = std::move(_value);
    return valueChanged;
}

bool DATCManagerStubDefault::validateSteeringWheelHeaterAttributeRequestedValue(const bool &_value) {
    (void)_value;
    return true;
}

void DATCManagerStubDefault::setSteeringWheelHeaterAttribute(const std::shared_ptr<CommonAPI::ClientId> _client, bool _value) {
    (void)_client;
    setSteeringWheelHeaterAttribute(_value);
}

void DATCManagerStubDefault::onRemoteSteeringWheelHeaterAttributeChanged() {
    // No operation in default
}

void DATCManagerStubDefault::RemoteEventHandler::onRemoteSteeringWheelHeaterAttributeChanged() {
    assert(defaultStub_ !=NULL);
    defaultStub_->onRemoteSteeringWheelHeaterAttributeChanged();
}

bool DATCManagerStubDefault::RemoteEventHandler::onRemoteSetSteeringWheelHeaterAttribute(bool _value) {
    assert(defaultStub_ !=NULL);
    return defaultStub_->trySetSteeringWheelHeaterAttribute(std::move(_value));
}

bool DATCManagerStubDefault::RemoteEventHandler::onRemoteSetSteeringWheelHeaterAttribute(const std::shared_ptr<CommonAPI::ClientId> _client, bool _value) {
    (void)_client;
    return onRemoteSetSteeringWheelHeaterAttribute(_value);
}

const ::v1::com::ivis::DATCManager::DATCManagerTypes::SeatHeaters& DATCManagerStubDefault::getSeatHeatersAttribute() {
    return seatHeatersAttributeValue_;
}

const ::v1::com::ivis::DATCManager::DATCManagerTypes::SeatHeaters& DATCManagerStubDefault::getSeatHeatersAttribute(const std::shared_ptr<CommonAPI::ClientId> _client) {
    (void)_client;
    return getSeatHeatersAttribute();
}

void DATCManagerStubDefault::setSeatHeatersAttribute(::v1::com::ivis::DATCManager::DATCManagerTypes::SeatHeaters _value) {
    const bool valueChanged = trySetSeatHeatersAttribute(std::move(_value));
    if (valueChanged) {
        fireSeatHeatersAttributeChanged(seatHeatersAttributeValue_);
    }
}

bool DATCManagerStubDefault::trySetSeatHeatersAttribute(::v1::com::ivis::DATCManager::DATCManagerTypes::SeatHeaters _value) {
    if (!validateSeatHeatersAttributeRequestedValue(_value))
        return false;

    const bool valueChanged = (seatHeatersAttributeValue_ != _value);
    seatHeatersAttributeValue_ = std::move(_value);
    return valueChanged;
}

bool DATCManagerStubDefault::validateSeatHeatersAttributeRequestedValue(const ::v1::com::ivis::DATCManager::DATCManagerTypes::SeatHeaters &_value) {
    (void)_value;
    return true;
}

void DATCManagerStubDefault::setSeatHeatersAttribute(const std::shared_ptr<CommonAPI::ClientId> _client, ::v1::com::ivis::DATCManager::DATCManagerTypes::SeatHeaters _value) {
    (void)_client;
    setSeatHeatersAttribute(_value);
}

void DATCManagerStubDefault::onRemoteSeatHeatersAttributeChanged() {
    // No operation in default
}

void DATCManagerStubDefault::RemoteEventHandler::onRemoteSeatHeatersAttributeChanged() {
    assert(defaultStub_ !=NULL);
    defaultStub_->onRemoteSeatHeatersAttributeChanged();
}

bool DATCManagerStubDefault::RemoteEventHandler::onRemoteSetSeatHeatersAttribute(::v1::com::ivis::DATCManager::DATCManagerTypes::SeatHeaters _value) {
    assert(defaultStub_ !=NULL);
    return defaultStub_->trySetSeatHeatersAttribute(std::move(_value));
}

bool DATCManagerStubDefault::RemoteEventHandler::onRemoteSetSeatHeatersAttribute(const std::shared_ptr<CommonAPI::ClientId> _client, ::v1::com::ivis::DATCManager::DATCManagerTypes::SeatHeaters _value) {
    (void)_client;
    return onRemoteSetSeatHeatersAttribute(_value);
}

const ::v1::com::ivis::DATCManager::DATCManagerTypes::SeatCoolers& DATCManagerStubDefault::getSeatCoolersAttribute() {
    return seatCoolersAttributeValue_;
}

const ::v1::com::ivis::DATCManager::DATCManagerTypes::SeatCoolers& DATCManagerStubDefault::getSeatCoolersAttribute(const std::shared_ptr<CommonAPI::ClientId> _client) {
    (void)_client;
    return getSeatCoolersAttribute();
}

void DATCManagerStubDefault::setSeatCoolersAttribute(::v1::com::ivis::DATCManager::DATCManagerTypes::SeatCoolers _value) {
    const bool valueChanged = trySetSeatCoolersAttribute(std::move(_value));
    if (valueChanged) {
        fireSeatCoolersAttributeChanged(seatCoolersAttributeValue_);
    }
}

bool DATCManagerStubDefault::trySetSeatCoolersAttribute(::v1::com::ivis::DATCManager::DATCManagerTypes::SeatCoolers _value) {
    if (!validateSeatCoolersAttributeRequestedValue(_value))
        return false;

    const bool valueChanged = (seatCoolersAttributeValue_ != _value);
    seatCoolersAttributeValue_ = std::move(_value);
    return valueChanged;
}

bool DATCManagerStubDefault::validateSeatCoolersAttributeRequestedValue(const ::v1::com::ivis::DATCManager::DATCManagerTypes::SeatCoolers &_value) {
    (void)_value;
    return true;
}

void DATCManagerStubDefault::setSeatCoolersAttribute(const std::shared_ptr<CommonAPI::ClientId> _client, ::v1::com::ivis::DATCManager::DATCManagerTypes::SeatCoolers _value) {
    (void)_client;
    setSeatCoolersAttribute(_value);
}

void DATCManagerStubDefault::onRemoteSeatCoolersAttributeChanged() {
    // No operation in default
}

void DATCManagerStubDefault::RemoteEventHandler::onRemoteSeatCoolersAttributeChanged() {
    assert(defaultStub_ !=NULL);
    defaultStub_->onRemoteSeatCoolersAttributeChanged();
}

bool DATCManagerStubDefault::RemoteEventHandler::onRemoteSetSeatCoolersAttribute(::v1::com::ivis::DATCManager::DATCManagerTypes::SeatCoolers _value) {
    assert(defaultStub_ !=NULL);
    return defaultStub_->trySetSeatCoolersAttribute(std::move(_value));
}

bool DATCManagerStubDefault::RemoteEventHandler::onRemoteSetSeatCoolersAttribute(const std::shared_ptr<CommonAPI::ClientId> _client, ::v1::com::ivis::DATCManager::DATCManagerTypes::SeatCoolers _value) {
    (void)_client;
    return onRemoteSetSeatCoolersAttribute(_value);
}


void DATCManagerStubDefault::requestGetSupportedTemperatureRange(const std::shared_ptr<CommonAPI::ClientId> _client, requestGetSupportedTemperatureRangeReply_t _reply) {
    (void)_client;
    _reply();
}

void DATCManagerStubDefault::requestSetTargetTemperature(const std::shared_ptr<CommonAPI::ClientId> _client, ::v1::com::ivis::DATCManager::DATCManagerTypes::EAreaType _areaType, double _temperature, requestSetTargetTemperatureReply_t _reply) {
    (void)_client;
    (void)_areaType;
    (void)_temperature;
    _reply();
}

void DATCManagerStubDefault::requestSetTargetTemperatureByDelta(const std::shared_ptr<CommonAPI::ClientId> _client, ::v1::com::ivis::DATCManager::DATCManagerTypes::EAreaType _areaType, double _temperatureDelta, requestSetTargetTemperatureByDeltaReply_t _reply) {
    (void)_client;
    (void)_areaType;
    (void)_temperatureDelta;
    _reply();
}

void DATCManagerStubDefault::requestGetSupportedFanDirection(const std::shared_ptr<CommonAPI::ClientId> _client, requestGetSupportedFanDirectionReply_t _reply) {
    (void)_client;
    _reply();
}

void DATCManagerStubDefault::requestGetSupportedFanSpeedRange(const std::shared_ptr<CommonAPI::ClientId> _client, requestGetSupportedFanSpeedRangeReply_t _reply) {
    (void)_client;
    _reply();
}

void DATCManagerStubDefault::requestSetFanSpeed(const std::shared_ptr<CommonAPI::ClientId> _client, ::v1::com::ivis::DATCManager::DATCManagerTypes::EAreaType _areaType, uint16_t _fanSpeed, requestSetFanSpeedReply_t _reply) {
    (void)_client;
    (void)_areaType;
    (void)_fanSpeed;
    _reply();
}

void DATCManagerStubDefault::requestSetFanSpeedByDelta(const std::shared_ptr<CommonAPI::ClientId> _client, ::v1::com::ivis::DATCManager::DATCManagerTypes::EAreaType _areaType, uint16_t _fanSpeedDelta, requestSetFanSpeedByDeltaReply_t _reply) {
    (void)_client;
    (void)_areaType;
    (void)_fanSpeedDelta;
    _reply();
}

void DATCManagerStubDefault::requestGetSupportedDefrostTarget(const std::shared_ptr<CommonAPI::ClientId> _client, requestGetSupportedDefrostTargetReply_t _reply) {
    (void)_client;
    _reply();
}

void DATCManagerStubDefault::requestGetSteeringWheelHeaterSupported(const std::shared_ptr<CommonAPI::ClientId> _client, requestGetSteeringWheelHeaterSupportedReply_t _reply) {
    (void)_client;
    _reply();
}

void DATCManagerStubDefault::requestGetSeatHeaterSupported(const std::shared_ptr<CommonAPI::ClientId> _client, requestGetSeatHeaterSupportedReply_t _reply) {
    (void)_client;
    _reply();
}

void DATCManagerStubDefault::requestGetSeatCoolerSupported(const std::shared_ptr<CommonAPI::ClientId> _client, requestGetSeatCoolerSupportedReply_t _reply) {
    (void)_client;
    _reply();
}


void DATCManagerStubDefault::fireResponseGetSupportedTemperatureRangeEvent(const ::v1::com::ivis::DATCManager::DATCManagerTypes::TemperatureRange &_temperatureRange) {
    DATCManagerStub::fireResponseGetSupportedTemperatureRangeEvent(_temperatureRange);
}
void DATCManagerStubDefault::fireResponseSetTargetTemperatureEvent(const ::v1::com::ivis::DATCManager::DATCManagerTypes::EDatcControlResult &_result, const ::v1::com::ivis::DATCManager::DATCManagerTypes::EAreaType &_areaType, const double &_temperature) {
    if (!_result.validate()) {
        return;
    }
    if (!_areaType.validate()) {
        return;
    }
    DATCManagerStub::fireResponseSetTargetTemperatureEvent(_result, _areaType, _temperature);
}
void DATCManagerStubDefault::fireResponseGetSupportedFanDirectionEvent(const ::v1::com::ivis::DATCManager::DATCManagerTypes::SupportedFanDirectionList &_supportedFanDirectionList) {
    DATCManagerStub::fireResponseGetSupportedFanDirectionEvent(_supportedFanDirectionList);
}
void DATCManagerStubDefault::fireResponseSetFanDirectionEvent(const ::v1::com::ivis::DATCManager::DATCManagerTypes::EDatcControlResult &_result, const ::v1::com::ivis::DATCManager::DATCManagerTypes::EAreaType &_areaType, const ::v1::com::ivis::DATCManager::DATCManagerTypes::EHvacFanDirection &_fanDirection) {
    if (!_result.validate()) {
        return;
    }
    if (!_areaType.validate()) {
        return;
    }
    if (!_fanDirection.validate()) {
        return;
    }
    DATCManagerStub::fireResponseSetFanDirectionEvent(_result, _areaType, _fanDirection);
}
void DATCManagerStubDefault::fireResponseGetSupportedFanSpeedRangeEvent(const ::v1::com::ivis::DATCManager::DATCManagerTypes::FanSpeedRange &_fanSpeedRange) {
    DATCManagerStub::fireResponseGetSupportedFanSpeedRangeEvent(_fanSpeedRange);
}
void DATCManagerStubDefault::fireResponseSetFanSpeedEvent(const ::v1::com::ivis::DATCManager::DATCManagerTypes::EDatcControlResult &_result, const ::v1::com::ivis::DATCManager::DATCManagerTypes::EAreaType &_areaType, const uint16_t &_fanSpeed) {
    if (!_result.validate()) {
        return;
    }
    if (!_areaType.validate()) {
        return;
    }
    DATCManagerStub::fireResponseSetFanSpeedEvent(_result, _areaType, _fanSpeed);
}
void DATCManagerStubDefault::fireResponseGetSupportedDefrostTargetEvent(const ::v1::com::ivis::DATCManager::DATCManagerTypes::SupportedDefrostTargetList &_supportedDefrostTargetList) {
    DATCManagerStub::fireResponseGetSupportedDefrostTargetEvent(_supportedDefrostTargetList);
}
void DATCManagerStubDefault::fireResponseSetAirRecirculationEvent(const ::v1::com::ivis::DATCManager::DATCManagerTypes::EDatcControlResult &_result, const bool &_on) {
    if (!_result.validate()) {
        return;
    }
    DATCManagerStub::fireResponseSetAirRecirculationEvent(_result, _on);
}
void DATCManagerStubDefault::fireResponseGetSteeringWheelHeaterSupportedEvent(const bool &_steeringWheelHeaterSupported) {
    DATCManagerStub::fireResponseGetSteeringWheelHeaterSupportedEvent(_steeringWheelHeaterSupported);
}
void DATCManagerStubDefault::fireResponseSetSteeringWheelHeaterEvent(const ::v1::com::ivis::DATCManager::DATCManagerTypes::EDatcControlResult &_result, const bool &_on) {
    if (!_result.validate()) {
        return;
    }
    DATCManagerStub::fireResponseSetSteeringWheelHeaterEvent(_result, _on);
}
void DATCManagerStubDefault::fireResponseGetSeatHeaterSupportedEvent(const bool &_seatHeaterSupported) {
    DATCManagerStub::fireResponseGetSeatHeaterSupportedEvent(_seatHeaterSupported);
}
void DATCManagerStubDefault::fireResponseSetSeatHeaterEvent(const ::v1::com::ivis::DATCManager::DATCManagerTypes::EDatcControlResult &_result, const ::v1::com::ivis::DATCManager::DATCManagerTypes::EAreaType &_areaType, const bool &_on) {
    if (!_result.validate()) {
        return;
    }
    if (!_areaType.validate()) {
        return;
    }
    DATCManagerStub::fireResponseSetSeatHeaterEvent(_result, _areaType, _on);
}
void DATCManagerStubDefault::fireResponseGetSeatCoolerSupportedEvent(const bool &_seatCoolerSupported) {
    DATCManagerStub::fireResponseGetSeatCoolerSupportedEvent(_seatCoolerSupported);
}
void DATCManagerStubDefault::fireResponseSetSeatCoolerEvent(const ::v1::com::ivis::DATCManager::DATCManagerTypes::EDatcControlResult &_result, const ::v1::com::ivis::DATCManager::DATCManagerTypes::EAreaType &_areaType, const bool &_on) {
    if (!_result.validate()) {
        return;
    }
    if (!_areaType.validate()) {
        return;
    }
    DATCManagerStub::fireResponseSetSeatCoolerEvent(_result, _areaType, _on);
}


DATCManagerStubDefault::RemoteEventHandler::RemoteEventHandler(DATCManagerStubDefault *_defaultStub)
    : 
      defaultStub_(_defaultStub) {
}

} // namespace DATCManager
} // namespace ivis
} // namespace com
} // namespace v1
