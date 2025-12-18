/system reset-configuration

/interface bridge add name=bridgeY0
/interface bridge add name=bridgeY1

/interface bridge port remove [find interface=etherTUX3_E1]
/interface bridge port add bridge=bridge60 interface=etherTUX3_E1

/interface bridge port remove [find interface=etherTUX4_E1]
/interface bridge port add bridge=bridge60 interface=etherTUX4_E1

/interface bridge port remove [find interface=etherTUX2_E1]
/interface bridge port add bridge=bridge61 interface=etherTUX2_E1

/interface bridge port remove [find interface=etherTUX4_E2]
/interface bridge port add bridge=bridge61 interface=etherTUX4_E2

/interface bridge port remove [find interface=etherRC_ETHER2]
/interface bridge port add bridge=bridge61 interface=etherRC_ETHER2

/interface bridge port print brief






#new ips-------------------------------------------------------------

/system reset-configuration

/interface bridge add name=bridge112
/interface bridge add name=bridge212

/interface bridge port remove [find interface=ether3]
/interface bridge port add bridge=bridge112 interface=ether3

/interface bridge port remove [find interface=ether4]
/interface bridge port add bridge=bridge112 interface=ether4

/interface bridge port remove [find interface=ether2]
/interface bridge port add bridge=bridge212 interface=ether2

/interface bridge port remove [find interface=ether5]
/interface bridge port add bridge=bridge212 interface=ether5

/interface bridge port remove [find interface=ether10]
/interface bridge port add bridge=bridge212 interface=ether10

/interface bridge port print brief
