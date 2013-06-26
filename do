#!/bin/sh

## Receives the serial port responsible for the communication as a parameter

PORT=$1

g++ -o exe listener.cpp
cat < $PORT &
./exe > $PORT
