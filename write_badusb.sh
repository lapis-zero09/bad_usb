#!/bin/bash

set -eu

avr-gcc -mmcu=attiny13a -Wall -Os -o out.elf $1
avr-objcopy -j .text -j .data -O ihex out.elf out.hex
avrdude -p t13 -c ftdi232 -U flash:w:out.hex
