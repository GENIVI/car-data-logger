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

#include "log.h"

#include <boost/shared_ptr.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/attributes/named_scope.hpp>

#define UNUSED(x) (void)(x)

void init_log(boost::log::trivial::severity_level logLevel, bool printScope)
{
    boost::log::core::get()->set_filter( boost::log::trivial::severity >= logLevel );

#if 0
    boost::log::add_common_attributes();
    boost::log::core::get()->add_global_attribute("Scope", boost::log::attributes::named_scope());

    auto fmtTimeStamp = boost::log::expressions::format_date_time<boost::posix_time::ptime>("TimeStamp", "%H:%M:%S.%f");
    auto fmtSeverity = boost::log::expressions::attr<boost::log::trivial::severity_level>("Severity");
    auto fmtScope = boost::log::expressions::format_named_scope("Scope",
                                                                boost::log::keywords::format = "%n",
                                                                boost::log::keywords::iteration = boost::log::expressions::reverse,
                                                                boost::log::keywords::depth = 1);

    boost::log::formatter logFmt;

    if ( printScope )
    {
        logFmt = boost::log::expressions::format("[%1%] [%2%] \t %3% \t <%4%>")
                % fmtTimeStamp % fmtSeverity
                % boost::log::expressions::smessage % fmtScope;
    }
    else
    {
        logFmt = boost::log::expressions::format("[%1%] [%2%] \t %3%")
                % fmtTimeStamp % fmtSeverity
                % boost::log::expressions::smessage;
    }

    /* console sink */
    auto consoleSink = boost::log::add_console_log(std::clog);
    consoleSink->set_formatter(logFmt);
#else
    UNUSED(printScope);
#endif
}
