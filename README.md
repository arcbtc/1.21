# 1.21 - a cheap to run/make lightning-network slave module


## Rationale
The bitcoin lightning-network makes possible very small and fast bitcoin transactions. When making real-world small transactions, usability and low power consumption is important. Previous IOT implementations, such as candy machines, rely on the device running a lightning node and usually an energy consuming output like a tablet. The approach of 1.21 is to have a single well balanced lightning node in a secure location (MASTER), communicating with low-powered (SLAVE) public IOT devices. 

With usability in mind 1.21 initially utilises Acinq Strike https://strike.acinq.co/, a quick to setup LN custodial service. However, if the shit hits the fan, 1.21 devices could very easily switch to a private LN node.

https://www.youtube.com/embed/Sa8vW9udCa0

## Hardware needed

* ESP32 (without built in OLED!)
* Waveshare 1.54inch Epaper module
* NPN Transistor (optional)
* Wires and stuff

## Limitations 

I'm an imbecile. This project would not of been possible without the kind help from folks at Fulmo's lightning-network hackdays http://fulmo.org/. The project has been developed for demonstration purposes only, although it is surprisingly stable, and with a little work the project could be secure and production ready. 

## Possible future improvements 

* Optional access point broadcast from ESP32 for changing the wifi, description and sats amount (probably triggered by a physical switch).
* Deep sleep power-saving mode when the device has been idle for a while.
* Discuss with Acinq ability to search payment requests by description, to make it easier for multiple devices to be requesting payments.


![alt text](https://i.imgur.com/dZMuadn.jpg)

