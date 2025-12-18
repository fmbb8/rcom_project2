#!/bin/bash
echo "Configuring Tux2 (Subnet 61)..."

# IP Configuration
sudo ifconfig if_e1 172.16.Y1.1/24

# Specific Route to Neighbor Subnet (60.0)
# We keep this to speak directly to Tux4 for internal traffic
sudo route add -net 172.16.Y0.0/24 gw 172.16.Y1.253

# Default Gateway
sudo route add -net 172.16.1.0/24 gw 172.16.Y1.254

# DNS Configuration
echo "nameserver 10.227.20.3" | sudo tee /etc/resolv.conf

echo "Tux2 Ready."



#new ips-----------------------------------------------------

#!/bin/bash
echo "Configuring Tux2 (Subnet 212)..."

# IP Configuration
sudo ifconfig if_e1 172.16.212.1/24

# Specific Route to Neighbor Subnet (60.0)
# We keep this to speak directly to Tux4 for internal traffic
sudo route add -net 172.16.112.0/24 gw 172.16.212.11

# Default Gateway
sudo route add -net 172.16.1.0/24 gw 172.16.212.254

# DNS Configuration
echo "nameserver 10.227.20.3" | sudo tee /etc/resolv.conf

echo "Tux2 Ready."