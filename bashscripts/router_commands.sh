# 1. Reset Configuration
/system reset-configuration

# 2. Configure Internal IP on Ether2
/ip address add address=172.16.61.254/24 interface=ether2

# 3. Enable NAT (Masquerade)
/ip firewall nat add chain=srcnat action=masquerade out-interface=ether1

# 4. Add Static Route to Subnet 60 (The "Hidden" Network)
/ip route add dst-address=172.16.60.0/24 gateway=172.16.61.253

# 5. Add Default Route (Gateway to the Lab/Internet)
/ip route add dst-address=0.0.0.0/0 gateway=172.16.1.254

# 6. Verify Routes
/ip route print