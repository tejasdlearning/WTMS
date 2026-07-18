#!/usr/bin/env bash
# Upload HouseNode firmware (auto-detect port)
set -e
cd "$(dirname "$0")/.."
~/.platformio/penv/bin/platformio run --target upload -e heltec_wifi_lora_32_V3
