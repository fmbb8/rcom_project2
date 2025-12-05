# 1. Reset Configuration
/system reset-configuration

# 2. Create Bridges
/interface bridge add name=bridge60
/interface bridge add name=bridge61

# 3. Assign Ports to Bridge 60 (Tux3-e1 & Tux4-e1)
# Remove from default bridge first, then add to bridge60
/interface bridge port remove [find interface=etherA]
/interface bridge port add bridge=bridge60 interface=etherA

/interface bridge port remove [find interface=etherB]
/interface bridge port add bridge=bridge60 interface=etherB

# 4. Assign Ports to Bridge 61 (Tux4-e2, Tux2-e1 & RC)
/interface bridge port remove [find interface=etherC]
/interface bridge port add bridge=bridge61 interface=etherC

/interface bridge port remove [find interface=etherD]
/interface bridge port add bridge=bridge61 interface=etherD

/interface bridge port remove [find interface=etherE]
/interface bridge port add bridge=bridge61 interface=etherE

# 5. Verify
/interface bridge port print brief