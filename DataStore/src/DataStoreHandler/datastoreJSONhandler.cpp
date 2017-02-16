#include "datastoreJSONhandler.h"
#include "filemanager.h"
#include "storagemanager.h"
#include "commonlogheader.h"

#define FOOTER_SEEK_POSITION -2
#define HEADER_STRING_FORMAT "{\n[\n"
#define FOOTER_STRING_FORMAT "\n]\n}"

DataStoreJSONHandler::DataStoreJSONHandler(FileManager *fileManager, StorageManager *storageManager)
    :m_fileManager(fileManager), m_storageManager(storageManager), m_latestFileName("")
{

}

DataStoreJSONHandler::~DataStoreJSONHandler()
{

}

void DataStoreJSONHandler::stop()
{
    if( !m_latestFileName.empty() )
    {
        addJSONFooter(m_latestFileName);

        m_fileManager->requestUpdateFileInfo(UpdateFileInfoType::UPDATE_FILE_SAVE_FINISHED, m_latestFileName);
    }
}

bool DataStoreJSONHandler::storeData(vector<DataStoreJSONHandler::CDL_DATA> *cdlDataList)
{
    string dataFormat = convertToJSON(cdlDataList);

    m_storageManager->manageStorage(dataFormat.length());

    if( m_latestFileName.empty() )
    {
        if( !createNewFile() )
        {
            return false;
        }
    }

    if(  m_storageManager->isFileExceedSizeLimit(dataFormat.length(), m_latestFileName) )
    {
        addJSONFooter(m_latestFileName);

        m_fileManager->requestUpdateFileInfo(UpdateFileInfoType::UPDATE_FILE_SAVE_FINISHED, m_latestFileName);

        if( !createNewFile() )
        {
            return false;
        }

        BOOST_LOG_TRIVIAL( debug ) << boost::format( "==================================================================================" );
        BOOST_LOG_TRIVIAL( debug ) << boost::format( "<< DataStoreJSONHandler::storeData() >> File size is not enough to save CDL data" );
        BOOST_LOG_TRIVIAL( debug ) << boost::format( "< Create New File Name : %s" ) % m_latestFileName;
        BOOST_LOG_TRIVIAL( debug ) << boost::format( "==================================================================================" );
    }

    if( !writeData(m_latestFileName, dataFormat) )
    {
        BOOST_LOG_TRIVIAL( error ) << boost::format( "<< DataStoreJSONHandler::storeData >> Failed to StoreData to file(.json)" );
        return false;
    }

    BOOST_LOG_TRIVIAL( debug ) << boost::format( "================================================================================" );
    BOOST_LOG_TRIVIAL( debug ) << boost::format( "<< DataStoreJSONHandler::storeData() >> Succeed to save CDL data in JSON file" );
    BOOST_LOG_TRIVIAL( debug ) << boost::format( "================================================================================" );

    return true;
}

bool DataStoreJSONHandler::writeData(const string filePath, string cdlJSONData)
{
    boost::filesystem::ofstream file;

    if( isFileEmpty(filePath) )
    {
        addJSONHeader(filePath);
    }

    boost::filesystem::path path(filePath);
    file.open(path, ios_base::in | ios_base::out);
    file.seekp(0, ios_base::end);
    if( !file.is_open() )
    {
        BOOST_LOG_TRIVIAL( error ) << boost::format( "<< DataStoreJSONHandler::writeData >> Failed to file open to write data in JSON file");
        return false;
    }

    file.write(cdlJSONData.c_str(), cdlJSONData.length());

    return true;
}


string DataStoreJSONHandler::convertToJSON(vector<CDL_DATA> *cdlDataList)
{
    string jsonDataFormat;
    for( unsigned int index=0; index<cdlDataList->size(); index++ )
    {
        jsonDataFormat.append(boost::str( boost::format( "{\"id\":\"%s\", \"value\":\"%s\", \"name\":\"%s\", \"type\":\"%s\", \"unit\":\"%s\",\"valid_state\":\"%s\", \"time_stamp\":\"%s\"},\n" )
                           % cdlDataList->at(index).id % cdlDataList->at(index).value % cdlDataList->at(index).name % cdlDataList->at(index).type
                            % cdlDataList->at(index).unit % cdlDataList->at(index).valid_state % cdlDataList->at(index).time_stamp));
    }

    return jsonDataFormat;
}

bool DataStoreJSONHandler::createNewFile()
{
    boost::filesystem::ofstream file;

    string newFilename = m_fileManager->createNewFileName();
    boost::filesystem::path path(newFilename);

    file.open(path);

    if( !file.is_open() )
    {
        BOOST_LOG_TRIVIAL( error ) << boost::format( "<< DataStoreJSONHandler::createNewFile >> Failed to create new file ( fileName: %s)") % m_latestFileName;
        return false;
    }

    m_latestFileName = newFilename;

    m_fileManager->requestUpdateNewFileCreated(m_latestFileName);

    file.close();

    return true;
}

void DataStoreJSONHandler::addJSONHeader(const string filePath)
{
    boost::filesystem::ofstream file;
    boost::filesystem::path path(filePath);

    string header;

    file.open(path, ios_base::in | ios_base::out);

    header.append(HEADER_STRING_FORMAT);
    file.write(header.c_str(), header.length());

    file.close();
}

void DataStoreJSONHandler::addJSONFooter(const string filePath)
{
    boost::filesystem::ofstream file;
    boost::filesystem::path path(filePath);

    string footer;

    file.open(path, ios_base::in | ios_base::out);

    footer.append(FOOTER_STRING_FORMAT);
    file.seekp(FOOTER_SEEK_POSITION, ios_base::end);
    file.write(footer.c_str(), footer.length());
    file.close();
}

bool DataStoreJSONHandler::isFileEmpty(const string filePath)
{
    boost::filesystem::ofstream file;
    boost::filesystem::path path(filePath);

    file.open(path, ios_base::in | ios_base::out);

    if( file.is_open() )
    {
        file.seekp(0, ios_base::end);

        int fileSize = file.tellp();
        file.close();

        if( fileSize == 0 )
        {
            return true;
        }
    }

    return false;
}
