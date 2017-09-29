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

#ifndef OFFBOARDPROVIDER_H
#define OFFBOARDPROVIDER_H

#include <Python.h>
#include <string>
#include <iostream>
#include <functional>

#include <boost/thread.hpp>

using namespace std;

class RVIDataManager;
class RVIClient;

class OffBoardProvider
{
public:
    OffBoardProvider();
    virtual ~OffBoardProvider();

public:
    virtual bool init();
    virtual void transferData(string filePath);
    virtual void stop();

private:
    void transferFileData(string filePath);

private:
    RVIDataManager * m_dataManager;
    RVIClient * m_rviClient;

    boost::mutex m_eventMutex;
    boost::mutex::scoped_lock m_eventLock;
    boost::condition_variable m_eventCondition;

    string m_aes256Key;
    string m_aes256IV;
};

#endif // OFFBOARDPROVIDER_H
