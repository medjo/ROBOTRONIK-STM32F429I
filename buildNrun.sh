#!/bin/sh
gnome-terminal -e "make"
telnet localhost 4444
sleep 1
reset halt
flash write_image erase main.hex
reset run
