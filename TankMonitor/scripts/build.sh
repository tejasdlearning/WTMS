#!/usr/bin/env bash
# Build TankMonitor
set -e
cd "$(dirname "$0")/.."
~/.platformio/penv/bin/platformio run
