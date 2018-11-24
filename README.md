# 1.21 (a cheap to run/make lightning-network slave module)


## Rationale
The bitcoin lightning-network makes possible very small and fast bitcoin transactions. When making real-world small transactions, usability and low power consumption is important. Previous IOT implementations, such as candy machines, rely on the device running a lightning node. The approach of 1.21 takes to have a single well balanced lightning node in a secure location (MASTER), communicating with (SLAVE) public IOT devices. 

With usability in mind 1.21 initially utilises Acinq Strike, a quick to setup LN custodial service. If the shit hits the fan, 1.21 devices could very easily switch to a private LN node.

## Hardware needed

* ESP32 (without built in OLED)
* Waveshare 1.54inch Epaper module
* NPN Transistor (optional)
* Wires and stuff

