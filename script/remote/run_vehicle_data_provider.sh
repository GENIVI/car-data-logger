#! /bin/bash

route add -net 224.0.0.0 netmask 224.0.0.0 eth0

script_file=$(cd ${0%/*} && echo $PWD/${0##*/}) # makes the path absolute, incl. the script's file name
script_path=${script_file%/*}   # dirname command: extracts the path

export COMMONAPI_CONFIG=$script_path/commonapi.ini
export LD_LIBRARY_PATH=$script_path/lib:$LD_LIBRARY_PATH

export VSOMEIP_APPLICATION_NAME=vehicle-data-provider
export VSOMEIP_CONFIGURATION=$script_path/json/vsomeip-vehicle-data-provider.json

export QT_QPA_PLATFORM=wayland
export QT_WAYLAND_DISABLE_WINDOWDECORATION=1

$script_path/bin/vehicle-data-provider &

