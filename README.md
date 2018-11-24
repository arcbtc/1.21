# 1.21 - Cheap to run/make lightning-network slave module


# Rationale
The bitcoin lightning-network makes possible very small and fast bitcoin transactions. When making real-world small transactions, usability and low power consumption is important. Previous IOT implementations, such as candy machines, rely on the device running a lightning node. The approach of 1.21 is to have a single well balanced lightning node in a secure location (MASTER), communicating with a (SLAVE) IOT device. 
