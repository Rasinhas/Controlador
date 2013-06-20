#!/bin/sh
cat < /dev/cu.usbmodemfd131 &
./listener.c > /dev/cu.usbmodemfd131
