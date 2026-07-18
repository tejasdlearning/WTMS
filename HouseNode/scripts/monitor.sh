#!/usr/bin/env bash
# Open serial monitor for HouseNode
set -e
cd "$(dirname "$0")/.."
~/.platformio/penv/bin/platformio device monitor --port /dev/cu.usbserial-0001 --baud 115200
