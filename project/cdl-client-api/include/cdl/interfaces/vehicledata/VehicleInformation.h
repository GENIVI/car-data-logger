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
 * \file VehicleInformation.h
*/

#ifndef VEHICLEINFORMATIONDEFINE
#define VEHICLEINFORMATIONDEFINE

#include "VehicleData.h"

namespace VehicleData
{

namespace VehicleInformation
{

// string
// WMI (World Manufacturer Identifier as defined by SAE) information for this vehicle. It's 3 bytes long characters.
static const std::string ID_WMI                             = "wmi";

// string
// VIN (Vehicle Identification Number as defined by ISO 3779) information for this vehicle. It's 17 bytes long characters.
static const std::string ID_VIN                             = "vin";

// unsigned short
// what type of this vehicle.
static const std::string ID_VEHCILE_TYPE                    = "vehicletype";

enum VehicleType
{
    VEHICLETYPE_SEDAN = 1,
    VEHICLETYPE_COUPE = 2,
    VEHICLETYPE_CABRIOLET = 3,
    VEHICLETYPE_ROADSTER = 4,
    VEHICLETYPE_SUV = 5,
    VEHICLETYPE_TRUCK = 6,
};


// unsigned short
// number of doors in first row.
static const std::string ID_DOOR_TYPE_FIRST_ROW             = "doortype_1strow";

// unsigned short
// number of doors in second row.
static const std::string ID_DOOR_TYPE_SECOND_ROW            = "doortype_2ndrow";

// unsigned short
// number of doors in third row.
static const std::string ID_DOOR_TYPE_THIRD_ROW             = "doortype_3rdrow";

// unsigned short
// type of fuel this vehicle uses. Types are defined by OBD-II.
static const std::string ID_FUEL_TYPE                       = "fueltype";

enum FuelType
{
    FUELTYPE_GASOLINE = 0x01,
    FUELTYPE_METHANOL= 0x02,
    FUELTYPE_ETHANOL = 0x03,
    FUELTYPE_DIESEL= 0x04,
    FUELTYPE_LPG = 0x05,
    FUELTYPE_CNG = 0x06,
    FUELTYPE_PROPANE = 0x07,
    FUELTYPE_ELECTRIC = 0x08,
    FUELTYPE_BIFUELRUNNINGGASOLINE = 0x09,
    FUELTYPE_BIFUELRUNNINGMETHANOL = 0x0A,
    FUELTYPE_BIFUELRUNNINGETHANOL = 0x0B,
    FUELTYPE_BIFUELRUNNINGLPG = 0x0C,
    FUELTYPE_BIFUELRUNNINGCNG = 0x0D,
    FUELTYPE_BIFUELRUNNINGPROP = 0x0E,
    FUELTYPE_BIFUELRUNNINGELECTRICITY = 0x0F,
    FUELTYPE_BIFUELMIXEDGASELECTRIC= 0x10,
    FUELTYPE_HYBRIDGASOLINE = 0x11,
    FUELTYPE_HYBRIDETHANOL = 0x12,
    FUELTYPE_HYBRIDDIESEL = 0x13,
    FUELTYPE_HYBRIDELECTRIC = 0x14,
    FUELTYPE_HYBRIDMIXEDFUEL = 0x15,
    FUELTYPE_HYBRIDREGENERATIVE = 0x16,
};

// unsigned short
// the transmission gear type of this vehicle
static const std::string ID_TRANSMISSION_GEAR_TYPE          = "transmissiongeartype";

enum TransmissionGearType
{
    TRANSMISSIONGEARTYPE_AUTO = 1,
    TRANSMISSIONGEARTYPE_MANUAL = 2,
    TRANSMISSIONGEARTYPE_CVT = 3,
};

// double
// radius of Wheel. It's information for GPS Dead Reckoning.
static std::string ID_WHEEL_INFO_RADIUS                     = "wheelinfo_radius";


// double
// wheel track. It's information for GPS Dead Reckoning.
static std::string ID_WHEEL_INFO_TRACK                      = "wheelinfo_track";

}

}

#endif // VEHICLEINFORMATIONDEFINE

