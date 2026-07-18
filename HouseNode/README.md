# HouseNode

LoRa receiver for tank monitoring (Heltec WiFi LoRa 32 V3).

Features:
- Continuous LoRa receive using RadioLib
- Heartbeat messages to confirm receiver is running
- Prints received payloads with RSSI and SNR

Quick commands (run from project root):

Build:

```bash
~/.platformio/penv/bin/platformio run
```

Upload:

```bash
~/.platformio/penv/bin/platformio run --target upload -e heltec_wifi_lora_32_V3
```

Open serial monitor:

```bash
~/.platformio/penv/bin/platformio device monitor --port /dev/cu.usbserial-0001 --baud 115200
```

Notes:
- `Serial.begin()` is initialized early so boot prints are visible.
- The receiver uses `radio.setDio1Action()` and `radio.startReceive()`.

To initialize Git and push this project, run:

```bash
cd HouseNode
git init
git add .
git commit -m "chore(init): add receiver code and README"
# Add remote then push
# git remote add origin <your-repo-url>
# git push -u origin main
```
