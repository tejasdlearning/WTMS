#include <Arduino.h>
#include <heltec_unofficial.h>

#define FREQUENCY 866.3
#define BANDWIDTH 250.0
#define SPREADING_FACTOR 9
#define TRANSMIT_POWER 2
#define TX_INTERVAL_MS 5000
// Hardware pins (adjust as needed for your wiring)
// `FLOAT_PIN` should be wired to the float switch (connect to GND when full)
// `BUZZER_PIN` should drive the buzzer (use a transistor if required)
#define FLOAT_PIN 35
#define BUZZER_PIN 25

void setup() {
  Serial.begin(115200);
  heltec_setup();

  Serial.println("Initializing LoRa transmitter...");

  if (radio.begin() != RADIOLIB_ERR_NONE) {
    Serial.println("Radio init failed");
    while (true) {}
  }

  radio.setFrequency(FREQUENCY);
  radio.setBandwidth(BANDWIDTH);
  radio.setSpreadingFactor(SPREADING_FACTOR);
  radio.setOutputPower(TRANSMIT_POWER);
  radio.setSyncWord(0x12);
  radio.setCRC(true);
  radio.setCodingRate(1);
  radio.setPreambleLength(8);

  Serial.println("Starting periodic HELLO every 5s...");
  int16_t state = radio.transmit("HELLO");
  Serial.print("TX state: ");
  Serial.println(state);

  // Buzzer & float sensor setup
  pinMode(FLOAT_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);
}

void loop() {
  heltec_loop();
  static uint32_t lastTx = 0;
  static bool lastFullState = false;
  static uint32_t buzzerLastToggle = 0;
  static bool buzzerState = false;

  // Read float sensor (assumes switch closes to GND when tank is FULL)
  bool isFull = (digitalRead(FLOAT_PIN) == LOW);
  if (isFull != lastFullState) {
    lastFullState = isFull;
    Serial.printf("Float sensor changed: %s\n", isFull ? "FULL" : "NOT FULL");
  }

  // If full, toggle buzzer at ~2 Hz; otherwise ensure buzzer is off
  if (isFull) {
    if (millis() - buzzerLastToggle >= 250) {
      buzzerLastToggle = millis();
      buzzerState = !buzzerState;
      digitalWrite(BUZZER_PIN, buzzerState ? HIGH : LOW);
    }
  } else {
    if (buzzerState) {
      buzzerState = false;
      digitalWrite(BUZZER_PIN, LOW);
    }
  }
  if (millis() - lastTx >= TX_INTERVAL_MS) {
    lastTx = millis();
    Serial.println("Transmitting HELLO");
    int16_t s = radio.transmit("HELLO");
    Serial.print("TX state: ");
    Serial.println(s);
  }
}