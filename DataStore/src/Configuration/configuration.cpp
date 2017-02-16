#include "configuration.h"
#include "commonlogheader.h"

#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

DataStoreConfiguration::DataStoreConfiguration()
    :m_dataStoreLocation(""), m_maxFileSize(0), m_maxStorageSize(0)
    ,m_fileExpirePeriod(0), m_transactionBufferSize(0)
{

}

DataStoreConfiguration::~DataStoreConfiguration()
{

}

bool DataStoreConfiguration::read(const string jsonFilePath)
{
    property_tree::ptree jsonDoc;

    try
    {
        property_tree::json_parser::read_json(jsonFilePath, jsonDoc);
    }
    catch(std::exception & e)
    {
        BOOST_LOG_TRIVIAL( error ) << boost::format( "<< ConfigurationManager::read() >> Failed to read json : %1%" ) % e.what();

        return false;
    }

    if( !parseStoreConfigFile(jsonDoc) )
    {
        return false;
    }

    return true;
}

string DataStoreConfiguration::getDataStoreLocation()
{
    return m_dataStoreLocation;
}

int DataStoreConfiguration::getMaxFileSize()
{
    return m_maxFileSize;
}

int DataStoreConfiguration::getMaxStorageSize()
{
    return m_maxStorageSize;
}

int DataStoreConfiguration::getFileExpirePeriod()
{
    return m_fileExpirePeriod;
}

int DataStoreConfiguration::getTransactionBufferSize()
{
    return m_transactionBufferSize;
}

bool DataStoreConfiguration::parseStoreConfigFile(property_tree::ptree &jsonDoc)
{
    if( jsonDoc.empty() )
    {
        BOOST_LOG_TRIVIAL( error ) << boost::format( "<< ConfigurationManager::parseStoreConfigFile() >> JSON file is empty" );
        return false;
    }

    BOOST_FOREACH( property_tree::ptree::value_type & value_type, jsonDoc )
    {
        string objName = value_type.first.data();

        if( !objName.compare("DataStoreLocation") )
        {
            m_dataStoreLocation = value_type.second.data();
            checkDataStoreLocation();
        }
        else if( !objName.compare("MaxFileSize") )
        {
            m_maxFileSize = stoi(value_type.second.data());
        }
        else if( !objName.compare("MaxStorageSize") )
        {
            m_maxStorageSize = stoi(value_type.second.data());
        }
        else if( !objName.compare("MaxFileExpirePeriod") )
        {
            m_fileExpirePeriod = stoi(value_type.second.data());
        }
        else if( !objName.compare("TransactionBufferSize") )
        {
            m_transactionBufferSize = stoi(value_type.second.data());
        }
        else
        {
            BOOST_LOG_TRIVIAL( warning ) << boost::format( "No configuration list : %s" ) % objName;
        }
    }

    if( !checkConfigInfo() )
    {
        return false;
    }

    return true;
}

bool DataStoreConfiguration::checkConfigInfo()
{
    if( m_dataStoreLocation.empty() )
    {
        BOOST_LOG_TRIVIAL( error ) << boost::format( "<< DataStoreConfiguration::checkConfigInfo() >> DataStoreLocation is invalid path ( %s )" )
                                       % m_dataStoreLocation;
        return false;
    }

    if( m_maxFileSize <= 0 )
    {
        BOOST_LOG_TRIVIAL( error ) << boost::format( "<< DataStoreConfiguration::checkConfigInfo() >> MaxFileSize is invalid value ( %d )" )
                                      % m_maxFileSize;
        return false;
    }

    if( m_maxStorageSize <= 0 )
    {
        BOOST_LOG_TRIVIAL( error ) << boost::format( "<< DataStoreConfiguration::checkConfigInfo() >> MaxStorageSize is invalid value ( %d )" )
                                      % m_maxStorageSize;
        return false;
    }

    if( m_fileExpirePeriod <= 0 )
    {
        BOOST_LOG_TRIVIAL( error ) << boost::format( "<< DataStoreConfiguration::checkConfigInfo() >> FileExpirePeriod is invalid value ( %d )" )
                                      % m_fileExpirePeriod;
        return false;
    }

    if( m_transactionBufferSize <= 0 )
    {
        BOOST_LOG_TRIVIAL( error ) << boost::format( "<< DataStoreConfiguration::checkConfigInfo() >> TransactionBufferSize is invalid value ( %d )" )
                                      % m_transactionBufferSize;
        return false;
    }

    return true;
}

void DataStoreConfiguration::checkDataStoreLocation()
{
    string checkDataStoreLocation;

    checkDataStoreLocation.push_back(m_dataStoreLocation.back());

    if( checkDataStoreLocation.compare("/") )
    {
        m_dataStoreLocation.append("/");
    }
}
