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

#include "vssitem.h"

VssItem::VssItem()
    : m_name(""), m_type(Data_Type_Max), m_unit(""),
      m_id(0), m_min(0), m_max(0),
      m_hasUnitValue(false), m_hasMinValue(false), m_hasMaxValue(false), m_hasEnumValue(false)
{
    m_vssEnumValueList.clear();
}

VssItem::~VssItem()
{

}

string VssItem::convertToValueString(const char *data)
{
    string convertedValue = "";

    switch ( m_type )
    {
    case branch:
    {
        break;
    }
    case UInt8:
    {
        UInt8_t value = 0;
        memcpy(&value, data, sizeof(UInt8_t));

        convertedValue = to_string(value);

        break;
    }
    case Int8:
    {
        Int8_t value = 0;
        memcpy(&value, data, sizeof(Int8_t));

        convertedValue = to_string(value);

        break;
    }
    case UInt16:
    {
        UInt16_t value = 0;
        memcpy(&value, data, sizeof(UInt16_t));

        convertedValue = to_string(value);

        break;
    }
    case Int16:
    {
        Int16_t value = 0;
        memcpy(&value, data, sizeof(Int16_t));

        convertedValue = to_string(value);

        break;
    }
    case UInt32:
    {
        UInt32_t value = 0;
        memcpy(&value, data, sizeof(UInt32_t));

        convertedValue = to_string(value);

        break;
    }
    case Int32:
    {
        Int32_t value = 0;
        memcpy(&value, data, sizeof(Int32_t));

        convertedValue = to_string(value);

        break;
    }
    case UInt64:
    {
        UInt64_t value = 0;
        memcpy(&value, data, sizeof(UInt64_t));

        convertedValue = to_string(value);

        break;
    }
    case Int64:
    {
        Int64_t value = 0;
        memcpy(&value, data, sizeof(Int64_t));

        convertedValue = to_string(value);

        break;
    }
    case Boolean:
    {
        bool value = 0;
        memcpy(&value, data, sizeof(bool));
        convertedValue = to_string(value);

        break;
    }
    case Float:
    {
        float value = 0;
        memcpy(&value, data, sizeof(float));

        convertedValue = to_string(value);

        break;
    }
    case Double:
    {
        double value = 0;
        memcpy(&value, data, sizeof(double));

        convertedValue = to_string(value);

        break;
    }
    case String:
    {
        convertedValue = data;

        break;
    }
    case ByteBuffer:
    {
        break;
    }
    default:
    {
        BOOST_LOG_TRIVIAL( warning ) << boost::format( "<< convertToValueString() >> This data is not VSS value type" );
        break;
    }
    }

    return convertedValue;
}

bool VssItem::validateData(const char *data)
{
    bool validatedResult = false;

    switch ( m_type )
    {
    case branch:
    {
        break;
    }
    case UInt8:
    {
        UInt8_t value = 0;
        memcpy(&value, data, sizeof(UInt8_t));

        if( value >= (UInt8_t)getMinValue() && value <= (UInt8_t)getMaxValue() )
        {
            validatedResult = true;
        }


        break;
    }
    case Int8:
    {
        Int8_t value = 0;
        memcpy(&value, data, sizeof(Int8_t));

        if( value >= (Int8_t)getMinValue() && value <= (Int8_t)getMaxValue() )
        {
            validatedResult = true;
        }

        break;
    }
    case UInt16:
    {
        UInt16_t value = 0;
        memcpy(&value, data, sizeof(UInt16_t));

        if( value >= (UInt16_t)getMinValue() && value <= (UInt16_t)getMaxValue() )
        {
            validatedResult = true;
        }

        break;
    }
    case Int16:
    {
        Int16_t value = 0;
        memcpy(&value, data, sizeof(Int16_t));

        if( value >= (Int16_t)getMinValue() && value <= (Int16_t)getMaxValue() )
        {
            validatedResult = true;
        }

        break;
    }
    case UInt32:
    {
        UInt32_t value = 0;
        memcpy(&value, data, sizeof(UInt32_t));

        if( value >= (UInt32_t)getMinValue() && value <= (UInt32_t)getMaxValue() )
        {
            validatedResult = true;
        }

        break;
    }
    case Int32:
    {
        Int32_t value = 0;
        memcpy(&value, data, sizeof(Int32_t));

        if( value >= (Int32_t)getMinValue() && value <= (Int32_t)getMaxValue() )
        {
            validatedResult = true;
        }

        break;
    }
    case UInt64:
    {
        UInt64_t value = 0;
        memcpy(&value, data, sizeof(UInt64_t));

        if( value >= (UInt64_t)getMinValue() && value <= (UInt64_t)getMaxValue() )
        {
            validatedResult = true;
        }

        break;
    }
    case Int64:
    {
        Int64_t value = 0;
        memcpy(&value, data, sizeof(Int64_t));

        if( value >= (Int64_t)getMinValue() && value <= (Int64_t)getMaxValue() )
        {
            validatedResult = true;
        }

        break;
    }
    case Boolean:
    {
        bool value = 0;
        memcpy(&value, data, sizeof(bool));

        if( value == true || value == false )
            validatedResult = true;

        break;
    }
    case Float:
    {
        float value = 0;
        memcpy(&value, data, sizeof(float));

        if( value >= (float)getMinValue() && value <= (float)getMaxValue() )
        {
            validatedResult = true;
        }

        break;
    }
    case Double:
    {
        double value = 0;
        memcpy(&value, data, sizeof(double));

        if( value >= (double)getMinValue() && value <= (double)getMaxValue() )
        {
            validatedResult = true;
        }

        break;
    }
    case String:
    {
        string value(data);
        vector<string> vssEnum = getVssEnumValueList();

        for(int index=0; index<(int)vssEnum.size(); index++)
        {
            if( !vssEnum.at(index).compare(value) )
            {
                validatedResult=true;
                setEnumValue(index);
            }
        }

        break;
    }
    case ByteBuffer:
    {
        break;
    }
    default:
    {
        BOOST_LOG_TRIVIAL( warning ) << boost::format( "<< validateData() >> This data is not VSS value type" );
        break;
    }
    }

    return validatedResult;
}

VssData_Type_e VssItem::convertDataTypeToEnum(string type)
{
    VssData_Type_e jsonDataType = Data_Type_Max;

    if(!type.compare("UInt8"))
    {
        jsonDataType = UInt8;
    }
    else if(!type.compare("Int8"))
    {
        jsonDataType = Int8;
    }
    else if(!type.compare("UInt16"))
    {
        jsonDataType = UInt16;
    }
    else if(!type.compare("Int16"))
    {
        jsonDataType = Int16;
    }
    else if(!type.compare("UInt32"))
    {
        jsonDataType = UInt32;
    }
    else if(!type.compare("Int32"))
    {
        jsonDataType = Int32;
    }
    else if(!type.compare("UInt64"))
    {
        jsonDataType = UInt64;
    }
    else if(!type.compare("Int64"))
    {
        jsonDataType = Int32;
    }
    else if(!type.compare("Boolean"))
    {
        jsonDataType = Boolean;
    }
    else if(!type.compare("Float"))
    {
        jsonDataType = Float;
    }
    else if(!type.compare("Double"))
    {
        jsonDataType = Double;
    }
    else if(!type.compare("String"))
    {
        jsonDataType = String;
    }
    else if(!type.compare("ByteBuffer"))
    {
        jsonDataType = ByteBuffer;
    }

    return jsonDataType;
}

void VssItem::setName(string nameValue)
{
    m_name = nameValue;
}

void VssItem::setType(string typeValue)
{
    m_type = convertDataTypeToEnum(typeValue);
}

void VssItem::setUnit(string unitValue)
{
    setHasUnitValue(true);
    m_unit = unitValue;
}

void VssItem::setID(string idValue)
{
    uint32_t id;
    stringstream(idValue) >> id;
    m_id = id;
}

void VssItem::setDefaultValue(string defaultValue)
{
    m_defaultValue = defaultValue;
}

void VssItem::setMinValue(string minValue)
{
    setHasMinValue(true);
    uint32_t min;
    stringstream(minValue) >> min;
    m_min = min;
}

void VssItem::setMaxValue(string maxValue)
{
    setHasMaxValue(true);
    uint32_t max;
    stringstream(maxValue) >> max;
    m_max = max;
}

void VssItem::setValue(string value)
{
    m_value = value;
}

void VssItem::setHasUnitValue(bool hasUnit)
{
    m_hasUnitValue = hasUnit;
}

void VssItem::setHasMinValue(bool hasMin)
{
    m_hasMinValue = hasMin;
}

void VssItem::setHasMaxValue(bool hasMax)
{
    m_hasMaxValue = hasMax;
}

void VssItem::setHasEnumValue(bool hasEnum)
{
    m_hasEnumValue = hasEnum;
}

void VssItem::setVssEnumValueList(vector<string> enumValueList)
{
    setHasEnumValue(true);
    m_vssEnumValueList = enumValueList;
}

void VssItem::setEnumValue(int enumValue)
{
    m_enumValue = enumValue;
}

string VssItem::getName()
{
    return m_name;
}

VssData_Type_e VssItem::getType()
{
    return m_type;
}

string VssItem::getUnit()
{
    return m_unit;
}

uint32_t VssItem::getID()
{
    return m_id;
}

string VssItem::getDefaultValue()
{
    return m_defaultValue;
}

int VssItem::getMinValue()
{
    return m_min;
}

int VssItem::getMaxValue()
{
    return m_max;
}

string VssItem::getValue()
{
    return m_value;
}

bool VssItem::getHasUnitValue()
{
    return m_hasUnitValue;
}

bool VssItem::getHasMinValue()
{
    return m_hasMinValue;
}

bool VssItem::getHasMaxValue()
{
    return m_hasMaxValue;
}

bool VssItem::getHasEnumValue()
{
    return m_hasEnumValue;
}

vector<string> VssItem::getVssEnumValueList()
{
    return m_vssEnumValueList;
}

int VssItem::getEnumValue()
{
    return m_enumValue;
}
