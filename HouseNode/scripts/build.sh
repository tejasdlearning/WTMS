#!/usr/bin/env bash
# Build HouseNode
set -e
cd "$(dirname "$0")/.."
~/.platformio/penv/bin/platformio run
