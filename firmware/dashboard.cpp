// Adapted from Progress Report 1, page 15. Completed for Arduino ESP32.
#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

// Set these locally before uploading; do not commit real credentials.
const char* ssid = "YOUR_WIFI";
const char* password = "YOUR_PASS";
constexpr uint8_t LIGHT_PIN = 2;
WebServer server(80);

void dashboard() {
  const char* html = R"HTML(<!DOCTYPE html><html>
<head><meta name="viewport" content="width=device-width,initial-scale=1">
<title>ESP32 Dashboard</title></head><body><h1>Light Control</h1>
<a href="/on"><button>Turn ON</button></a>
<a href="/off"><button>Turn OFF</button></a></body></html>)HTML";
  server.send(200, "text/html", html);
}
void setLight(bool on) {
  digitalWrite(LIGHT_PIN, on ? HIGH : LOW);
  server.sendHeader("Location", "/");
  server.send(303, "text/plain", "");
}
void setup() {
  Serial.begin(115200);
  pinMode(LIGHT_PIN, OUTPUT);
  digitalWrite(LIGHT_PIN, LOW);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("Connecting to Wi-Fi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print('.');
  }
  Serial.println();
  Serial.println(WiFi.localIP());
  server.on("/", dashboard);
  server.on("/on", [] { setLight(true); });
  server.on("/off", [] { setLight(false); });
  server.begin();
}
void loop() { server.handleClient(); }
