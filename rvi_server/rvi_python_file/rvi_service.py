#!/usr/bin/python
#/*
#* Copyright (C) 2017, IVIS
#*
#* This file is part of GENIVI Project CDL - Car Data Logger.
#*
#* This Source Code Form is subject to the terms of the
#* Mozilla Public License (MPL), v. 2.0.
#* If a copy of the MPL was not distributed with this file,
#* You can obtain one at http://mozilla.org/MPL/2.0/.
#*
#* For further information see http://www.genivi.org/.
#*/
#
#/*!
#* \author Seok-Heum Choi <seokheum.choi@ivisolution.com>
#*
#* \copyright Copyright (c) 2017, IVIS \n
#* License MPL-2.0: Mozilla Public License version 2.0 http://mozilla.org/MPL/2.0/.
#*
#*/

import sys
from rvilib import RVI
import callback

def service_invoked(**args):
	print "[Python] Service invoked!"
	callback.CallBackTransDataFunc(args)	

def services_available(**args):
	print
	print "Python Services available!"
	print "args:", args 
	print
	return ['ok']

def services_unavailable(**args):
    print
    print "Python Services unavailable!"
    print "args:", args 
    print
    return ['ok']

def service_transmission_start(**args):
	print "Python service transmission_start()"
	callback.CallBackTransStartFunc(args)

def service_transmission_finish():
	print "Python service transmission finish()"
	callback.CallBackTransFinishFunc()

def init_service():
	print "[Python] init_service()"
	rvi.start_serve_thread()
	print "[Python] RVI node URL:        ", rvi_node_url
	full_service_name = rvi.register_service(transmission_send_data_service_name, service_invoked)
	print "[Python] Service:             ", full_service_name
	full_service_name = rvi.register_service(transmission_start_service_name, service_transmission_start)
	print "[Python] Service:             ", full_service_name
	full_service_name = rvi.register_service(transmission_finish_service_name, service_transmission_finish)
	print "[Python] Service:             ", full_service_name
	raw_input('Press enter to quit: ')
	rvi.unregister_service(service_name)
	rvi.shutdown()
	sys.exit(0)

rvi_node_url = "http://localhost:9001"

transmission_start_service_name = "transmission_start"
transmission_send_data_service_name = "transmission_data"
transmission_finish_service_name = "transmission_finish"

print "[Python] start service name : ", transmission_start_service_name
print "[Python] data service name : ", transmission_send_data_service_name
print "[Python] finish service name  : ", transmission_finish_service_name

full_service_name = "default"

rvi = RVI(rvi_node_url)

# Starting the thread that handles incoming calls is
# not really necessary since register_service will do it for us.

rvi.set_services_available_callback(services_available)
rvi.set_services_unavailable_callback(services_unavailable)

