# TankMonitor

LoRa transmitter for tank monitoring.

Features:
- Periodic `HELLO` transmitter for RF testing
- Float sensor input and buzzer output for local alert when tank is full

Quick commands (run from project root):

Build:

```bash
~/.platformio/penv/bin/platformio run
```

Upload (auto-detect port):

```bash
~/.platformio/penv/bin/platformio run --target upload -e heltec_wifi_lora_32_V3
```

Open serial monitor:

```bash
~/.platformio/penv/bin/platformio device monitor --port /dev/cu.usbserial-0001 --baud 115200
```

Hardware notes:
- Default `FLOAT_PIN` is 35 (expects switch to connect to GND when FULL).
- Default `BUZZER_PIN` is 25 (use a transistor or driver for passive buzzer).

Customize pins in `src/main.cpp` if your wiring differs.

Git:
- This project is in its own Git repo. To push commits, add a remote:

```bash
git remote add origin <your-repo-url>
git push -u origin feature/lora
```
