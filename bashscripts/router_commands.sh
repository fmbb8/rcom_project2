# 1. Reset Configuration
/system reset-configuration

# 2. Configure Internal IP on Ether1 and 2
/ip address add address=172.16.1.61/24 interface=ether1
/ip address add address=172.16.61.254/24 interface=ether2

# 4. Add Static Route to Subnet 60 (The "Hidden" Network)
/ip route add dst-address=172.16.60.0/24 gateway=172.16.61.253

# 6. Verify Routes
/ip route print
