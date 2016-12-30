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
* \author Seok-Heum Choi <seokheum.choi@ivisolution.com>
*
* \copyright Copyright (c) 2016, IVIS \n
* License MPL-2.0: Mozilla Public License version 2.0 http://mozilla.org/MPL/2.0/.
*
*/

#ifndef VSSITEM_H
#define VSSITEM_H

#include <unordered_map>
#include <string>
#include <iostream>
#include <sstream>
#include <boost/variant.hpp>

#include "commonlogheader.h"

using namespace std;

typedef unsigned char       UInt8_t;
typedef signed char         Int8_t;
typedef unsigned short      UInt16_t;
typedef signed short        Int16_t;
typedef unsigned int        UInt32_t;
typedef signed int          Int32_t;
typedef unsigned long long  UInt64_t;
typedef signed long long    Int64_t;
typedef string              String_t;
typedef boost::variant<UInt8_t, Int8_t, UInt16_t, Int16_t, UInt32_t, Int32_t, UInt64_t, Int64_t, bool, float, double, String_t> VssData_Variant;

typedef enum _JsonEnumType{
    branch=0,
    UInt8,      //1
    Int8,       //2
    UInt16,     //3
    Int16,      //4
    UInt32,     //5
    Int32,      //6
    UInt64,     //7
    Int64,      //8
    Boolean,    //9
    Float,      //10
    Double,     //11
    String,     //12
    ByteBuffer, //13

    Data_Type_Max
}VssData_Type_e;

/**
 *
 * @brief Provide the functions to set and get infomation of data.
 *
 * This class will be used in VSSJsonParser to set the infomation of data defined in VSS JSON file.
 * Also it will be used in DataValidationService to get the infomation of data.
 *
 * VssData_Variant is Variant type.
 *
 * [Infomation of Data] : type, name, unit, ID, min, max, enum value etc.
 *
 * Since the min, max, unit and enum values are not defined in all data,
 * there exists functions that know existence.
 *
 */

class VssItem
{
public:
    VssItem();
    virtual ~VssItem();

public:
    /**
     * @brief Convert validated data to a string.
     *
     * @param data
     */
    string convertToValueString(const char * data);
    bool validateData(const char * data);

public:
    void setName(string name);
    void setType(string type);
    void setUnit(string unit);
    void setID(string id);
    void setDefaultValue(string defaultValue);
    void setMinValue(string min);
    void setMaxValue(string max);
    void setValue(string value);
    void setHasUnitValue(bool hasUnit);
    void setHasMinValue(bool hasMin);
    void setHasMaxValue(bool hasMax);
    void setHasEnumValue(bool hasEnum);
    void setVssEnumValueList(vector<string> enumValueList);
    void setEnumValue(int enumValue);

    string getName();
    VssData_Type_e getType();
    string getUnit();
    uint32_t getID();
    string getDefaultValue();
    int getMinValue();
    int getMaxValue();
    string getValue();
    bool getHasUnitValue();
    bool getHasMinValue();
    bool getHasMaxValue();
    bool getHasEnumValue();
    vector<string> getVssEnumValueList();
    int getEnumValue();

private:
    VssData_Type_e convertDataTypeToEnum(string type);

private:
    string m_name;
    VssData_Type_e m_type;
    string m_unit;
    uint32_t m_id;
    string m_defaultValue;
    int m_min;
    int m_max;
    string m_value;
    vector<string> m_vssEnumValueList;
    int m_enumValue;
    bool m_hasUnitValue;
    bool m_hasMinValue;
    bool m_hasMaxValue;
    bool m_hasEnumValue;
};

#endif // VSSITEM_H
