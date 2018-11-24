
# 1.21 - a cheap to run/make lightning-network slave module

## Rationale
The bitcoin lightning-network makes possible very small and fast bitcoin transactions. When making real-world small transactions, usability and low power consumption is important. Previous IoT implementations, such as candy machines, rely on the device running a lightning node and usually an energy consuming output like a tablet. The approach of 1.21 is to have a single well balanced lightning node in a secure location (MASTER), communicating with low-powered (SLAVE) public IoT devices. 

With usability in mind 1.21 initially utilises Acinq Strike https://strike.acinq.co/, a quick to setup LN custodial service. However, if the shit hits the fan, 1.21 devices could very easily switch to a private LN node.

[![LN Slave Mod](https://i.imgur.com/PN3KT0S.png)](https://www.youtube.com/watch?v=Sa8vW9udCa0)

## Hardware needed

* ESP32 (without built in OLED!)
* Waveshare 1.54inch Epaper module
* NPN Transistor (optional)
* Wires and stuff

## Notes

The project is written for the Arduino IDE, appropriate libraries in the includes will have to be downloaded separately.

I used a standard ESP32 board, recognised in the Arduino IDE as a "LOLIN D32", although the code could be fiddled to support most ESP32s (as long as they don't have an OLED screen!).

The trickiest part of the project was getting the ESP32 to build an appropriate byte-array image for the epaper from the QR code data - a more regular byte-array format, such as XBM, would not render correctly. https://javl.github.io/image2cpp/ was extremely helpful.

Epaper to ESP32 SPI connection example:
![SPI PINS image](https://i.imgur.com/4rdB2OC.jpg)

1.21 sends an ON to GPIO PIN 17 for 2 secs, which can be adjusted in the code: 

* GPIO PIN 17 is connected to the BASE of an NPN transistor
* The COLLECTOR of the NPN is connected to the same 3v PIN as the epaper
* The EMITTER of the NPN is connected to the live wire of the candy machine motor
* The ground of the motor is connected the GND PIN

## Limitations 

I'm an imbecile. This project would not have been possible without the kind help from folks at Fulmo's lightning-network hackdays http://fulmo.org/. The project has been developed for demonstration purposes only, although it is surprisingly stable, and with a little work the project could be secure and production ready. 

## Possible future improvements 

* Optional access point broadcast from ESP32 for changing the wifi, description and sats amount (probably triggered by a physical switch).
* Deep sleep power-saving mode when the device has been idle for a while.
* Discuss with Acinq ability to search payment requests by description, to make it easier for multiple devices to be requesting payments.


![flowchart image](https://i.imgur.com/dZMuadn.jpg)

