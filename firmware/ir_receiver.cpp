// Adapted from Progress Report 1, page 12; updated to IRremote 4.x.
#include <Arduino.h>
#define DECODE_NEC
#include <IRremote.hpp>
constexpr uint8_t IR_RECV_PIN = 27, RELAY_PIN = 25;
constexpr uint16_t IR_ADDRESS = 0;
constexpr uint8_t ON_COMMAND = 0xAA, OFF_COMMAND = 0xBB;
// Set LOW for an active-low relay module. Verify with a low-voltage load.
constexpr uint8_t RELAY_ON = HIGH;
constexpr uint8_t RELAY_OFF = RELAY_ON == HIGH ? LOW : HIGH;
void setup() {
  Serial.begin(115200);
  digitalWrite(RELAY_PIN, RELAY_OFF);
  pinMode(RELAY_PIN, OUTPUT);
  IrReceiver.begin(IR_RECV_PIN, DISABLE_LED_FEEDBACK);
}
void loop() {
  if (!IrReceiver.decode()) return;
  const auto data = IrReceiver.decodedIRData;
  IrReceiver.resume();
  if (data.protocol != NEC || data.address != IR_ADDRESS ||
      (data.flags & (IRDATA_FLAGS_IS_REPEAT | IRDATA_FLAGS_PARITY_FAILED | IRDATA_FLAGS_WAS_OVERFLOW))) return;
  if (data.command == ON_COMMAND) {
    digitalWrite(RELAY_PIN, RELAY_ON);
    Serial.println("Bulb: ON");
  } else if (data.command == OFF_COMMAND) {
    digitalWrite(RELAY_PIN, RELAY_OFF);
    Serial.println("Bulb: OFF");
  }
}
