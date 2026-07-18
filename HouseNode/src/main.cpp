// Adapted from Heltec LoRa example (LoRa_rx_tx)
#include <Arduino.h>
#define HELTEC_POWER_BUTTON
#include <heltec_unofficial.h>

// Pause between transmited packets in seconds. Set to 0 to only transmit on button.
#define PAUSE               300

#define FREQUENCY           866.3
#define BANDWIDTH           250.0
#define SPREADING_FACTOR    9
#define TRANSMIT_POWER      0

String rxdata;
volatile bool rxFlag = false;
long counter = 0;
uint64_t last_tx = 0;
uint64_t tx_time;
uint64_t minimum_pause;

void rx() {
  rxFlag = true;
}

void setup() {
  Serial.begin(115200);
  heltec_setup();
  Serial.println("Radio init");
  RADIOLIB_OR_HALT(radio.begin());

  // Set radio parameters
  Serial.printf("Frequency: %.2f MHz\n", FREQUENCY);
  RADIOLIB_OR_HALT(radio.setFrequency(FREQUENCY));
  Serial.printf("Bandwidth: %.1f kHz\n", BANDWIDTH);
  RADIOLIB_OR_HALT(radio.setBandwidth(BANDWIDTH));
  Serial.printf("Spreading Factor: %i\n", SPREADING_FACTOR);
  RADIOLIB_OR_HALT(radio.setSpreadingFactor(SPREADING_FACTOR));
  Serial.printf("TX power: %i dBm\n", TRANSMIT_POWER);
  RADIOLIB_OR_HALT(radio.setOutputPower(TRANSMIT_POWER));

  // Set the callback function for received packets
  radio.setDio1Action(rx);
  // Start receiving
  RADIOLIB_OR_HALT(radio.startReceive(RADIOLIB_SX126X_RX_TIMEOUT_INF));
  Serial.println("Receiver ready. Waiting for packets...");
}

void loop() {
  heltec_loop();

  bool tx_legal = millis() > last_tx + minimum_pause;
  static uint32_t lastHeartbeat = 0;
  if (millis() - lastHeartbeat > 5000) {
    lastHeartbeat = millis();
    Serial.println("Heartbeat: receiver alive");
  }
  // Transmit a packet every PAUSE seconds or when the button is pressed
  if ((PAUSE && tx_legal && millis() - last_tx > (PAUSE * 1000)) || button.isSingleClick()) {
    if (!tx_legal) {
      Serial.printf("Legal limit, wait %i sec.\n", (int)((minimum_pause - (millis() - last_tx)) / 1000) + 1);
      return;
    }
    Serial.printf("TX [%s] ", String(counter).c_str());
    radio.clearDio1Action();
    heltec_led(50);
    tx_time = millis();
    RADIOLIB(radio.transmit(String(counter++).c_str()));
    tx_time = millis() - tx_time;
    heltec_led(0);
    if (_radiolib_status == RADIOLIB_ERR_NONE) {
      Serial.printf("OK (%i ms)\n", (int)tx_time);
    } else {
      Serial.printf("fail (%i)\n", _radiolib_status);
    }
    minimum_pause = tx_time * 100;
    last_tx = millis();
    radio.setDio1Action(rx);
    RADIOLIB_OR_HALT(radio.startReceive(RADIOLIB_SX126X_RX_TIMEOUT_INF));
  }

  // If a packet was received, display it and the RSSI and SNR
  if (rxFlag) {
    rxFlag = false;
    radio.readData(rxdata);
    if (_radiolib_status == RADIOLIB_ERR_NONE) {
      Serial.printf("RX [%s]\n", rxdata.c_str());
      Serial.printf("  RSSI: %.2f dBm\n", radio.getRSSI());
      Serial.printf("  SNR: %.2f dB\n", radio.getSNR());
    } else {
      Serial.printf("Read failed (%i)\n", _radiolib_status);
    }
    RADIOLIB_OR_HALT(radio.startReceive(RADIOLIB_SX126X_RX_TIMEOUT_INF));
  }
}