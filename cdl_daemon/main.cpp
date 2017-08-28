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

#include "cdl_daemon.hpp"
#include "common/log.hpp"

#include <csignal>
#include <boost/asio.hpp>
#include <boost/asio/signal_set.hpp>
#include <boost/asio/impl/io_service.hpp>

#define UNUSED(x) (void)(x)

boost::asio::io_service io_service;

void exitHandler(boost::system::error_code error, int signal_number)
{
    UNUSED(signal_number);

    if ( !error )
    {
        io_service.stop();
        return;
    }
}

int main(int argc, char *argv[])
{
    init_log(boost::log::trivial::severity_level::info);

    CDLDaemon * cdlDaemon_instance = new CDLDaemon();

    if( cdlDaemon_instance != NULL )
    {
        cdlDaemon_instance->init();
    }

    boost::asio::signal_set io_signal(io_service, SIGINT, SIGTERM);

    io_signal.async_wait(exitHandler);
    io_service.run();

    cdlDaemon_instance->stop();
    delete cdlDaemon_instance;

    return 0;
}
