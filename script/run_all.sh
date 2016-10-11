#! /bin/bash

sudo route add -net 224.0.0.0 netmask 224.0.0.0 eth0

script_file=$(cd ${0%/*} && echo $PWD/${0##*/}) # makes the path absolute, incl. the script's file name
script_path=${script_file%/*}   # dirname command: extracts the path

$script_path/script/local/run_hu.sh &

$script_path/script/local/run_cluster.sh &
