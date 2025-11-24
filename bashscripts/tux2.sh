#!/bin/bash

echo "Configuring tux2..."

sudo ifconfig if_e1 172.16.61.1/24

sudo route add -net 172.16.60.0/24 gw 172.16.61.253

echo "tux2 configuration complete!"