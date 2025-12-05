#!/bin/bash
echo "Configuring Tux3 (Subnet 60)..."

# IP Configuration
sudo ifconfig if_e1 172.16.60.1/24

# Clean ARP
sudo ip neigh flush all

# Default Gateway
sudo route add default gw 172.16.60.254

# DNS Configuration
echo "nameserver 10.227.20.3" | sudo tee /etc/resolv.conf

echo "Tux3 Ready."