#include "storagemanager.h"
#include "filemanager.h"
#include "commonlogheader.h"
#include "configuration.h"

#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem.hpp>

#define KB_SIZE 1024
#define PERIOD_SIZE 60

StorageManager::StorageManager(DataStoreConfiguration *configManager, FileManager *fileManager)
    :m_configManager(configManager), m_fileManager(fileManager), m_storagePath("")
    ,m_maxFileSize(0), m_maxStorageSize(0), m_maxFileExpirePeriod(0)
{

}

StorageManager::~StorageManager()
{

}

bool StorageManager::init()
{
    m_storagePath = m_configManager->getDataStoreLocation();
    m_maxFileSize = (m_configManager->getMaxFileSize() * KB_SIZE);
    m_maxStorageSize = (m_configManager->getMaxStorageSize() * KB_SIZE);

    if( !createDataStoreLocation() )
    {
        return false;
    }

    return true;
}


void StorageManager::manageStorage(int dataSize)
{
    if( (m_maxStorageSize - getCurrentStorageUsageSize()) < dataSize )
    {
        requestDeleteOldestFile();
    }
}

bool StorageManager::isFileExceedSizeLimit(int dataSize, string filePath)
{
    if( (m_maxFileSize - getCurrentFileUsageSize(filePath)) < dataSize )
    {
        return true;
    }
    else
    {
        return false;
    }
}



void StorageManager::checkFileExpiredThread()
{
    //not implemented yet
}

int StorageManager::getCurrentFileUsageSize(string filePath)
{
    int size;
    boost::filesystem::path path(filePath);

    if( boost::filesystem::exists(path) )
    {
        size = boost::filesystem::file_size(path);
    }
    else
    {
        BOOST_LOG_TRIVIAL( error ) << boost::format( "<< StorageManager::checkCurrentUsingFileSize() >> File is not existed / FilePath : %s" ) % filePath;
        return 0;
    }

    return size;
}

int StorageManager::getCurrentStorageUsageSize()
{
    size_t size=0;

    boost::filesystem::directory_iterator end_iter;
    for( boost::filesystem::directory_iterator iter(m_storagePath); iter != end_iter; iter++ )
    {
        try
        {
            if( !boost::filesystem::is_directory(*iter) )
            {
                size += boost::filesystem::file_size(*iter);
            }
        }
        catch( std::exception &e )
        {
            BOOST_LOG_TRIVIAL( error ) << boost::format( "<< StorageManager::getCurrentStorageUsageSize >> retry calculate directory size ( err : %s)" ) % e.what();
            size = getCurrentStorageUsageSize();
        }
    }

    return size;
}

bool StorageManager::deleteFile(string oldestFilePath)
{
    boost::filesystem::path filePath(oldestFilePath);
    bool result;

    if( boost::filesystem::exists(filePath) )
    {
        result = boost::filesystem::remove_all(filePath);
    }

    if( result == 0 )
    {
        BOOST_LOG_TRIVIAL( error ) << boost::format( "Failed to delete file ( file name : %1% )" ) % oldestFilePath;
        return false;
    }

    return true;
}

void StorageManager::requestDeleteOldestFile()
{
    string oldestFileName = m_fileManager->searchFileName(SearchFileMothodType::OLDEST_FILE);

    if( !oldestFileName.empty() )
    {
        if( deleteFile(oldestFileName) )
        {
            // succeed to delete file ( update the file exist to false )
            m_fileManager->requestUpdateFileInfo(UpdateFileInfoType::UPDATE_FILE_DELETED, oldestFileName);
        }
        else
        {
            //failed to delete file ( update the file exist to error )
            m_fileManager->requestUpdateFileInfo(UpdateFileInfoType::UPDATE_FILE_DELETION_FAILED, oldestFileName);
        }
    }
    else
    {
        BOOST_LOG_TRIVIAL( error ) << boost::format( "Failed to search oldest file name");
    }

    BOOST_LOG_TRIVIAL( debug ) << boost::format( "================================================================================" );
    BOOST_LOG_TRIVIAL( debug ) << boost::format( "<< StorageManager::requestDeleteOldestFile() >> Succeed to delete oldest file" );
    BOOST_LOG_TRIVIAL( debug ) << boost::format( "< Oldest File Name : %s >" ) % oldestFileName;
    BOOST_LOG_TRIVIAL( debug ) << boost::format( "================================================================================" );
}

bool StorageManager::createDataStoreLocation()
{
    boost::filesystem::path directory_path(m_storagePath);

    if( !boost::filesystem::exists(directory_path) )
    {
        if( !boost::filesystem::create_directory(directory_path) )
        {
            BOOST_LOG_TRIVIAL( error ) << boost::format( "<< StorageManager::createDataStoreLocation() >> Failed to create storage ( dir path : %1% )" ) % m_storagePath;
            return false;
        }
    }
    else
    {
        if( boost::filesystem::is_directory(directory_path) )
        {
            return true;
        }
        else
        {
            BOOST_LOG_TRIVIAL( error ) << boost::format( "<< StorageManager::createDataStoreLocation() >> Specified path is not directory ( dir path : %1% )" ) % m_storagePath;
            return false;
        }
    }

    return true;
}
