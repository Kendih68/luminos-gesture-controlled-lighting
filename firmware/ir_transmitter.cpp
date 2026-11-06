// Adapted from Progress Report 1, page 12; updated to IRremote 4.x.
#include <Arduino.h>
#define DECODE_NEC
#include <IRremote.hpp>
constexpr uint8_t IR_LED_PIN = 26;
constexpr uint16_t IR_ADDRESS = 0;
constexpr uint8_t ON_COMMAND = 0xAA, OFF_COMMAND = 0xBB;
void sendON() {
  IrSender.sendNEC(IR_ADDRESS, ON_COMMAND, 0);
  Serial.println("IR Sent: ON");
}
void sendOFF() {
  IrSender.sendNEC(IR_ADDRESS, OFF_COMMAND, 0);
  Serial.println("IR Sent: OFF");
}
void setup() {
  Serial.begin(115200);
  IrSender.begin(IR_LED_PIN);
}
void loop() {
  // The report sample alternates ON/OFF; no gesture hook was supplied.
  sendON();
  delay(500);
  sendOFF();
  delay(500);
}
