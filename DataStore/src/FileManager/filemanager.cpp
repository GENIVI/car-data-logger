#include "filemanager.h"
#include "commonlogheader.h"
#include "configuration.h"

#include <boost/date_time/posix_time/posix_time.hpp>

FileManager::FileManager(DataStoreConfiguration *configManager, FileInfoDBHandler *fileInfoDBHandler)
    :m_configManager(configManager), m_fileInfoDBHandler(fileInfoDBHandler), m_fileInfoListFilePath("")
{

}

FileManager::~FileManager()
{

}

bool FileManager::init()
{
    m_storagePath = m_configManager->getDataStoreLocation();

    if( !createFileInfoListFile() )
    {
        return false;
    }

    return true;
}

bool FileManager::createFileInfoListFile()
{
    m_fileInfoListFilePath.append(m_storagePath).append(FileInfoListTableName);

    return m_fileInfoDBHandler->openFileInfoListFile(m_fileInfoListFilePath);
}
void FileManager::requestUpdateFileInfo(UpdateFileInfoType updateFileType, string filename)
{
    switch(updateFileType)
    {
    case UpdateFileInfoType::UPDATE_FILE_DELETED:
    case UpdateFileInfoType::UPDATE_FILE_PROVIDED:
    case UpdateFileInfoType::UPDATE_FILE_DELETION_FAILED:
    {
        if( !m_fileInfoDBHandler->updateFileInfo(updateFileType, filename) )
        {
            BOOST_LOG_TRIVIAL( error ) << boost::format( "<< FileManager::updateFileInfo() >> Failed to update data ( type : %d )" ) % updateFileType;
        }

        break;
    }
    case UpdateFileInfoType::UPDATE_FILE_SAVE_FINISHED:
    {
        string endTime = getCurrentDateTime();
        if( !m_fileInfoDBHandler->updateFileInfo(updateFileType, filename, endTime) )
        {
            BOOST_LOG_TRIVIAL( error ) << boost::format( "<< FileManager::updateFileInfo() >> Failed to update data ( type : %d )" ) % updateFileType;
        }

        break;
    }
    }

}

void FileManager::requestUpdateNewFileCreated(string filename)
{
    FileInfo fileInfo;
    fileInfo.start_time = getCurrentDateTime();
    fileInfo.end_time = "";
    fileInfo.fileName = filename;
    fileInfo.file_exist = "true";
    fileInfo.file_provide = "false";

    m_fileInfoDBHandler->addNewFileInfo(fileInfo);
}

string FileManager::createNewFileName()
{
    string fileName;
    string dateTimeFormat;

    dateTimeFormat = getCurrentDateTime();
    fileName.append(m_storagePath).append(dateTimeFormat).append(".json");

    return fileName;
}

string FileManager::searchFileName(SearchFileMothodType fileType)
{
    string fileName;

    fileName = m_fileInfoDBHandler->getFileName(fileType);

    return fileName;
}

string FileManager::getCurrentDateTime()
{
    boost::posix_time::ptime localTime =
                boost::posix_time::second_clock::local_time();

    string dateTimeFormat = boost::str( boost::format( "%04d%02d%02d_%2d%02d%02d" )
                                       % localTime.date().year() % static_cast<int>(localTime.date().month()) % localTime.date().day()
                                       % localTime.time_of_day().hours() % localTime.time_of_day().minutes() % localTime.time_of_day().seconds() );

    return dateTimeFormat;
}
