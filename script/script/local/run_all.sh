#! /bin/bash

sudo route add -net 224.0.0.0 netmask 224.0.0.0 eth0

script_file=$(cd ${0%/*} && echo $PWD/${0##*/}) # makes the path absolute, incl. the script's file name
script_path=${script_file%/*}   # dirname command: extracts the path

# start head-unit process
$script_path/run_hu.sh &

#start cluster unit process
$script_path/run_cluster.sh &

