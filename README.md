# PJ_Lepton_LWIR
  
# ============  
# Lepton LWIR  
# ============  
  
# correct transfer formula  
Y = (X * 0.0217 + A - 177.77);  
A: ambient temperature, default is 32  
X: target radiation  
Y: target temperature  
  
# guild  
compiler: cmake && make  
execute: ./raspberry_video  
execute bash: run_start.sh  
publisher.cpp: mqtt publisher  
LeptonThread.cpp: lepton lwir function  
  
# lwir_v0  
# ========  
base: official example version  
trigger by tof sensor and snap 5 frame to get temperature  
  
# lwir_v1  
# ========  
base: official example version  
trigger by tof sensor  
  
# lwir_v2  
# ========  
for smart meeting room version  
lepton lwir + mqtt_cpp  
