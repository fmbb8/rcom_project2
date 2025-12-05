#!/bin/bash

echo "Configuring tux4 (router)..."

sudo ifconfig if_e1 172.16.60.254/24
sudo ifconfig if_e2 172.16.61.253/24

sudo sysctl -w net.ipv4.ip_forward=1

sudo sysctl -w net.ipv4.icmp_echo_ignore_broadcasts=0

echo "tux4 router configuration complete!"