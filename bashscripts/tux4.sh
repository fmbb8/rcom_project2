#!/bin/bash
echo "Configuring Tux4 (Router)..."

# Configure e1 on Subnet 60 and e2 on Subnet 61
sudo ifconfig if_e1 172.16.60.254/24
sudo ifconfig if_e2 172.16.61.253/24

# Enable IP Forwarding
sudo sysctl -w net.ipv4.ip_forward=1
sudo sysctl -w net.ipv4.icmp_echo_ignore_broadcasts=0

# Default Gateway
sudo route add 172.16.1.0/24 gw 172.16.61.254

# DNS Configuration
echo "nameserver 10.227.20.3" | sudo tee /etc/resolv.conf

echo "Tux4 Ready."
