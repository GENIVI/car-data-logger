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

rvi_node = "http://localhost:9001"

transmission_start_service = "genivi.org/node/17f46d5a-e91f-438b-bc9b-55af49be86f6/transmission_start"
transmission_send_data_service = "genivi.org/node/17f46d5a-e91f-438b-bc9b-55af49be86f6/transmission_data"
transmission_finish_service = "genivi.org/node/17f46d5a-e91f-438b-bc9b-55af49be86f6/transmission_finish"

rvi = RVI(rvi_node)

def transmission_start(fileName, fileSize, fileTotalIndex):
	rvi_args = {'fileName':fileName, 'fileSize':fileSize, 'fileTotalIndex':fileTotalIndex}
	print "[Python] start cmd args : ", rvi_args
	rvi.message(transmission_start_service, rvi_args)

def transmission_data(curIndex, data):
	rvi_args = {'currentIndex': curIndex, 'data': data}
	print "[Python] data cmd args : ", rvi_args
	rvi.message(transmission_send_data_service, rvi_args)

def transmission_finish():
	rvi_args = {}
	rvi.message(transmission_finish_service, rvi_args)
	
