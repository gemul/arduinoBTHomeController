# arduinoBTHomeController
Arduino-based smart home controller using bluetooth.

## Library used
- DS3231 RTC Library [download here](http://www.rinkydinkelectronics.com/download.php?f=DS3231.zip)

## Hardware
- Arduino Nano V3
- HC-05 Bluetooth module
- DS3231 RTC Module
- 8ch Relay Module
- 4 digit 7 segment
- 74HC595 Shift Register

## Disclaimer
This is a work in progress.

## To-do
- ~~DS3231 Integration~~
- ~~Bluetooth~~
    - ~~Bluetooth Connectivity~~
    - ~~Bluetooth Command parser~~
    - ~~Bluetooth Command controller~~
- ~~RTC~~
    - ~~Set time command~~
    - ~~Set date command~~
    - ~~Set dow command~~
    - ~~Get time command~~
    - ~~Get date command~~
    - ~~Get dow command~~
    - ~~Get temperature command~~
- Shift register library integration [from here](https://github.com/gemul/ArduinoLibraries)
    - PINOUT(clock=4,latch=7,data=6)
- ~~Relay module integration~~
    - ~~74HC595~~
    - ~~Relay Commands~~
    - ~~...~~
- ~~7 segment display integration~~
    - ~~74HC595~~
    - ~~display commands~~
    - ~~...~~