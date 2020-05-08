# ATTiny13 UART TX
Sending Serial messages with ATTiny13A.  Majority of the code was used from [Marcel Meyer-Garcia](https://github.com/MarcelMG/AVR8_BitBang_UART_TX).
In order for this to work for me, I needed to have the internal clock on the ATTiny set to 9.6MHz without any subdivision.  I needed to make sure the default setting of dividing the clock by 8 (LOW.SCKDIV8) was removed. Under the fuse header below lists the fuses that needed to be reset.

## Software Requirements
1. Atmel Studio 7

## Hardware Requirements
1. [USB AVRISP XPII](https://www.mouser.com/ProductDetail/Seeed-Studio/105990010?qs=SElPoaY2y5IxLFrW85NJBw%3D%3D&gclid=EAIaIQobChMI7oabkY-J6QIVjZyzCh2AcATJEAQYASABEgJdOvD_BwE)
2. [ATTiny13A](https://www.mouser.com/ProductDetail/Microchip-Technology-Atmel/ATTINY13A-PU?qs=%2Fha2pyFadui6ZVxcaWvWt%252Bgs2kFpKu6OD%2F6dOI%252BYMKs%3D)
3. [5V Power Supply](https://www.adafruit.com/product/276)

## Fuses
HIGH FUSE - 0xFF
LOW FUSE - 0x3A


## Datasheets and External Links
1. [ATTiny13A Datasheet](http://ww1.microchip.com/downloads/en/DeviceDoc/doc8126.pdf)
