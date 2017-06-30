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

#ifndef OFFBOARDPROVIDERTESTAPP_H
#define OFFBOARDPROVIDERTESTAPP_H

#include <QObject>
#include <QVector>
#include <QTimer>

class OffBoardProvider;

class OffBoardProviderTestApp : public QObject
{
    Q_OBJECT

public:
    OffBoardProviderTestApp();
    virtual ~OffBoardProviderTestApp();

public:
    bool init();

public slots:
    void transferFileData();

private:
    void setFileStoragePath();
    bool setJSONFileLists();
    void printJSONFileLists();

private:
    OffBoardProvider * m_offBoardProvider;
    QString m_fileStoragePath;
    QVector<QString> m_fileList;
    QTimer * m_timer;
    int m_fileCount;
};

#endif // OFFBOARDPROVIDERTESTAPP_H
