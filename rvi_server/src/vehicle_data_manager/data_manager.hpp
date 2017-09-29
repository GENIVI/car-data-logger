/*
* Copyright (C) 2017, IVIS
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
* \copyright Copyright (c) 2017, IVIS \n
* License MPL-2.0: Mozilla Public License version 2.0 http://mozilla.org/MPL/2.0/.
*
*/

#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>
#include <QString>
#include <string>

using namespace std;

class DataManager : public QObject
{
    Q_OBJECT
public:
    explicit DataManager(QObject * parent = NULL);
    virtual ~DataManager();

public:
    static DataManager * getInstance();

private:
    void init();
    void createTransmissionResultStorage();
    string decryptData(string & aes256Key, string & aes256Iv, string & dataBuf);
    bool createResultFile(QString & resultFileStoragePath, string & decryptedData);

signals:
    void signalCompletedTransferData(QString jsonFilePath);
    void signalTransferCurrentFileIndex(int currentIndex, int totalIndex);
    void signalCompletedStoreFile(QString filePath);
    void signalFinishTransfer();

public slots:
    void slotTransmissionStart(QString fileName, int fileSize, int totalIndex);   //info ( filename , file size, send file total index )
    void slotTransmissionData(QString data, int currentIndex);
    void slotTransmissionFinish();

private:
    QString m_resultFileStoragePath;
    QString m_fileName;
    int m_fileSize;
    int m_totalIndex;
    string m_dataBuf;

    string m_aes256Key;
    string m_aes256IV;
};

#endif // DATAMANAGER_H
