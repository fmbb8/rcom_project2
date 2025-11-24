#!/bin/bash

echo "Configuring tux3..."

sudo ifconfig if_e1 172.16.60.1/24 up

sudo route add -net 172.16.61.0/24 gw 172.16.60.254

echo "tux3 configuration complete!"