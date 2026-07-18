# PlatformIO Projects Workspace

This workspace contains two PlatformIO projects:

- `TankMonitor` — LoRa transmitter with float sensor
- `HouseNode` — LoRa receiver with buzzer

Each project is independent. To build/upload/monitor a single module, `cd` into its directory and use the scripts under `scripts/` or run the `platformio` commands shown in each project's README.

Examples:

```bash
# Build TankMonitor
cd TankMonitor
./scripts/build.sh

# Upload HouseNode
cd HouseNode
./scripts/upload.sh

# Monitor TankMonitor serial
cd TankMonitor
./scripts/monitor.sh
```
