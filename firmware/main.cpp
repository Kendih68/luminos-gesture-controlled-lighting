// Luminos wearable controller and lantern firmware.
#include <Arduino.h>
#define DECODE_NEC
#include <IRremote.hpp>
#include "logic.h"

// Configure pins, address, thresholds, colors and timings for your hardware.
constexpr uint16_t ADDRESS = 0x4C55;
using luminos::Command;

#if defined(LUMINOS_WEARABLE)
#include <Wire.h>
#include <Adafruit_MPU6050.h>
constexpr uint8_t TX_PIN = 26, SDA_PIN = 21, SCL_PIN = 22;
Adafruit_MPU6050 sensor;
luminos::Gestures gestures;
uint32_t sampleTime = 0;
void setup() {
 Serial.begin(115200);
 Wire.begin(SDA_PIN, SCL_PIN);
 if (!sensor.begin()) {
  Serial.println("MPU6050 missing; no IR commands will be sent.");
  while (true) delay(1000);
 }
 sensor.setAccelerometerRange(MPU6050_RANGE_8_G);
 sensor.setFilterBandwidth(MPU6050_BAND_21_HZ);
 IrSender.begin(TX_PIN);
}
void loop() {
 const uint32_t now = millis();
 if (uint32_t(now - sampleTime) < 20) return;
 sampleTime = now;
 sensors_event_t a, g, temperature;
 if (!sensor.getEvent(&a, &g, &temperature)) return;
 const float magnitude = sqrtf(a.acceleration.x*a.acceleration.x +
     a.acceleration.y*a.acceleration.y + a.acceleration.z*a.acceleration.z);
 const Command command = gestures.update(a.acceleration.x, magnitude, now);
 if (command != Command::None) {
  IrSender.sendNEC(ADDRESS, static_cast<uint8_t>(command), 0);
  Serial.printf("IR command %u\n", static_cast<unsigned>(command));
 }
}
#elif defined(LUMINOS_LANTERN)
#include <Adafruit_NeoPixel.h>
constexpr uint8_t RX_PIN = 27, LED_PIN = 25;
constexpr uint16_t LED_COUNT = 16;
Adafruit_NeoPixel ring(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
luminos::Light light;
void render() {
 // Brightness capped at 64/255 by default, not a power guarantee.
 const uint8_t levels[] = {8, 16, 32, 64};
 const uint32_t colors[] = {ring.Color(255,0,0), ring.Color(0,255,0),
     ring.Color(0,0,255), ring.Color(255,128,0), ring.Color(128,0,255), ring.Color(0,255,255)};
 ring.setBrightness(light.white ? levels[light.level] : 32);
 ring.fill(!light.on ? 0 : (light.white ? ring.Color(255,255,255) : colors[light.color]));
 ring.show();
}
void setup() {
 Serial.begin(115200);
 ring.begin(); render(); // Off at boot.
 IrReceiver.begin(RX_PIN, DISABLE_LED_FEEDBACK);
}
void loop() {
 if (!IrReceiver.decode()) return;
 const auto data = IrReceiver.decodedIRData;
 IrReceiver.resume();
 if (data.protocol != NEC || data.address != ADDRESS ||
     data.command < 1 || data.command > 3 ||
     (data.flags & (IRDATA_FLAGS_IS_REPEAT | IRDATA_FLAGS_PARITY_FAILED | IRDATA_FLAGS_WAS_OVERFLOW))) return;
 if (light.apply(static_cast<Command>(data.command))) render();
}
#else
#error Select the wearable or lantern PlatformIO environment.
#endif
