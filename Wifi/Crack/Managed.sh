#!/bin/bash

airmon-ng
airmon-ng check kill
ip link set wlan1 down
iw dev wlan1 set type managed
ip link set wlan1 up
service network-manager restart
iw wlan1 info
