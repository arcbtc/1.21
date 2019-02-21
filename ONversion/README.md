

# 1.21 OpenNode Edition

## Rationale
This version of 1.21 sweet machine uses OpenNode. Set up a free account here 
https://opennode.co/join/f774f2a0-1377-45e2-b719-6b821f24900d

Watch the tutorial below for instructions on how to wire up the sweet machine.

[![LN Slave Mod](https://i.imgur.com/JYw6HYc.jpg)](https://www.youtube.com/watch?v=uMO651YS0y4)

## Hardware needed

* ESP32 (without built in OLED!)
* MH-ET-LIVE epaper module 
* NPN Transistor
* Electronic Sweet Machine (Global Gizmos Candy Dispenser)
* Wires and stuff

## Notes

The project is written for the Arduino IDE, appropriate libraries in the includes will have to be downloaded separately.

I used a standard ESP32 board, recognised in the Arduino IDE as a "LOLIN D32", although the code could be fiddled to support most ESP32s (as long as they don't have an OLED screen!).

Epaper to ESP32 SPI connection example:
![SPI PINS image](https://i.imgur.com/AB4DInM.jpg)

1.21 sends an ON to GPIO PIN 17 for 2 secs, which can be adjusted in the code: 

* GPIO PIN 17 is connected to the BASE of an NPN transistor
* The COLLECTOR of the NPN is connected to the same 3v PIN as the epaper
* The EMITTER of the NPN is connected to the live wire of the candy machine motor
* The ground of the motor is connected the GND PIN

## Limitations 

I'm an imbecile. This project would not have been possible without the kind help from folks at Fulmo's lightning-network hackdays http://fulmo.org/. The project has been developed for demonstration purposes only, although it is surprisingly stable, and with a little work the project could be secure and production ready. 


