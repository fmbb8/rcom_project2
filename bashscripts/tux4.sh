#!/bin/bash
echo "Configuring Tux4 (Router)..."

# Configure e1 on Subnet Y0 and e2 on Subnet Y1
sudo ifconfig if_e1 172.16.Y0.254/24
sudo ifconfig if_e2 172.16.Y1.253/24

# Enable IP Forwarding
sudo sysctl -w net.ipv4.ip_forward=1
sudo sysctl -w net.ipv4.icmp_echo_ignore_broadcasts=0

# Default Gateway
sudo route add -net 172.16.1.0/24 gw 172.16.Y1.254

# DNS Configuration
echo "nameserver 10.227.20.3" | sudo tee /etc/resolv.conf

echo "Tux4 Ready."


#new ips------------------------------------------------

#!/bin/bash
echo "Configuring Tux4 (Router)..."

# Configure e1 on Subnet Y0 and e2 on Subnet Y1
sudo ifconfig if_e1 172.16.112.10/24
sudo ifconfig if_e2 172.16.212.11/24

# Enable IP Forwarding
sudo sysctl -w net.ipv4.ip_forward=1
sudo sysctl -w net.ipv4.icmp_echo_ignore_broadcasts=0

# Default Gateway
sudo route add -net 172.16.1.0/24 gw 172.16.212.254

# DNS Configuration
echo "nameserver 10.227.20.3" | sudo tee /etc/resolv.conf

echo "Tux4 Ready."