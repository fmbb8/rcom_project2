/system reset-configuration

/ip address add address=172.16.1.Y1/24 interface=ether1
/ip address add address=172.16.Y1.254/24 interface=ether2

/ip route add dst-address=172.16.Y0.0/24 gateway=172.16.Y1.253

/ip route print


#new ips
/system reset-configuration

/ip address add address=172.16.1.121/24 interface=ether1
/ip address add address=172.16.212.254/24 interface=ether2

/ip route add dst-address=172.16.112.0/24 gateway=172.16.212.11

/ip route print