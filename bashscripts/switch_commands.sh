# 1. Reset Configuration
/system reset-configuration

# 2. Create Bridges
/interface bridge add name=bridge60
/interface bridge add name=bridge61

# 3. Assign Ports to Bridge 60 (Tux3-e1 & Tux4-e1)
# Remove from default bridge first, then add to bridge60
/interface bridge port remove [find interface=etherTUX3_E1]
/interface bridge port add bridge=bridge60 interface=etherTUX3_E1

/interface bridge port remove [find interface=etherTUX4_E1]
/interface bridge port add bridge=bridge60 interface=etherTUX4_E1

# 4. Assign Ports to Bridge 61 (Tux4-e2, Tux2-e1 & RC)
/interface bridge port remove [find interface=etherTUX2_E1]
/interface bridge port add bridge=bridge61 interface=etherTUX2_E1

/interface bridge port remove [find interface=etherTUX4_E2]
/interface bridge port add bridge=bridge61 interface=etherTUX4_E2

/interface bridge port remove [find interface=etherRC_ETHER2]
/interface bridge port add bridge=bridge61 interface=etherRC_ETHER2

# 5. Verify
/interface bridge port print brief
