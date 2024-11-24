#!/bin/bash

if [ -e $1 ]; then
    sudo python3 $1
elif [ "$1" == "clean_mininet" ]; then
    sudo mn -c
elif [ "$1" == "ins" ]; then
    sudo insmod ./tcp_simple_custom/reno_custom.ko
elif [ "$1" == "rmv" ]; then
    sudo rmmod reno_custom
elif [ "$1" == "chk" ]; then
    lsmod | grep reno_custom
elif [ "$1" == "cur" ]; then
    cat /proc/sys/net/ipv4/tcp_congestion_control
elif [ "$1" == "avl" ]; then
    cat /proc/sys/net/ipv4/tcp_available_congestion_control
elif [ "$1" == "chg" ]; then
    sudo sysctl net.ipv4.tcp_congestion_control=$2
fi
