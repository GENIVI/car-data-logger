#!/bin/bash

script_file=$(cd ${0%/*} && echo $PWD/${0##*/}) # makes the path absolute, incl. the script's file name
script_path=${script_file%/*}   # dirname command: extracts the path

export COMMONAPI_CONFIG=$script_path/../commonapi.ini
export VSOMEIP_APPLICATION_NAME=cdl-daemon
export VSOMEIP_CONFIGURATION=$script_path/../json/vsomeip-cdl-cluster-unit.json
export LD_LIBRARY_PATH=$script_path/../lib:$LD_LIBRARY_PATH

$script_path/../bin/cdl-daemon
