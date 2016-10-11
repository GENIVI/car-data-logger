#! /bin/bash

sudo route add -net 224.0.0.0 netmask 224.0.0.0 eth0

script_file=$(cd ${0%/*} && echo $PWD/${0##*/}) # makes the path absolute, incl. the script's file name
script_path=${script_file%/*}   # dirname command: extracts the path

export COMMONAPI_CONFIG=$script_path/../../commonapi.ini
export LD_LIBRARY_PATH=$script_path/../../lib:$LD_LIBRARY_PATH

$script_path/../../bin/av-hmi-application &
$script_path/../../bin/mode-manager &
$script_path/../../bin/media-manager &

$script_path/start_hu_av_information_provider.sh &

sleep 1

$script_path/start_headunit_vehicle_data_consumer-climates.sh &

sleep 1

$script_path/start_headunit_vehicle_data_consumer-running-status.sh &
