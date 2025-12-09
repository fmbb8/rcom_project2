#!/bin/bash
echo "Configuring Tux2 (Subnet 61)..."

# IP Configuration
sudo ifconfig if_e1 172.16.61.1/24

# Specific Route to Neighbor Subnet (60.0)
# We keep this to speak directly to Tux4 for internal traffic
sudo route add -net 172.16.60.0/24 gw 172.16.61.253

# Default Gateway
sudo route add -net 172.16.1.0/24 gw 172.16.61.254

# DNS Configuration
echo "nameserver 10.227.20.3" | sudo tee /etc/resolv.conf

echo "Tux2 Ready."
