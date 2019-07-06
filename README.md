# Morseduino
Morseduino is a simple Arduino based Morse code transmitter/receiver. It communicates via light and sound. It was created to be a fun and exploratory project of Morse code.

## Morse code
**#TODO:** write brief explanation of morse code and history

## Mode of operation
The transmitter receives an ASCII message from serial port, encodes it to Morse code symbols (dots and dashes), and transmits the symbols via light (using an LED) and via sound (using a buzzer).
The receiver decodes the light/audio message to symbols, and from that, to ASCII text and sends it to the serial port, for reading.

## Schematics
Below are presented the Fritzing schematics showing the hardware setup for both the transmitter and receiver, which are very similar.

**#TODO:** include Frizting schematics

## Installation & Usage
### Install
To install, simply open each project, compile it and flash on the respective Arduino board. 

### Use
Follow this simple steps:
1. Connect the Arduinos and the necessary electronic components according to schematics provided.
2. Connect the Arduinos to USB ports (it can be on same computer, or different ones)
3. Turn on two instances of a serial monitor (ex: Arduino IDE serial monitor and [CuteCom](http://cutecom.sourceforge.net/), or another), one for each port.
4. Send the message on the transmitter serial monitor and receive it on the other one.

## Project notes
* This project was developed using Arduino Nano V3. It should run without any problem on other Arduino boards.
* **The receiver code is not available yet. But you can tinker with the transmitter which is fully functional.**