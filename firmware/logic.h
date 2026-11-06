#pragma once
#include <cstdint>
#include <cmath>
namespace luminos {
enum class Command : uint8_t { None = 0, Color = 1, White = 2, Toggle = 3 };
class Gestures {
 bool initialized_ = false, armed_ = true, candidate_ = false, toggled_ = false;
 int direction_ = 0;
 float lastMagnitude_ = 0;
 uint32_t lastSample_ = 0, tiltStart_ = 0, lastToggle_ = 0;
public:
 // Generated choices: acceleration in m/s^2, clock in milliseconds.
 Command update(float x, float magnitude, uint32_t now) {
  if (!std::isfinite(x) || !std::isfinite(magnitude) || magnitude < 0) {
   initialized_ = false; candidate_ = false; return Command::None;
  }
  const uint32_t dt = now - lastSample_;
  const bool baseline = !initialized_ || dt > 250;
  const float jerk = baseline || dt == 0 ? 0 :
      std::fabs(magnitude - lastMagnitude_) * 1000.0f / dt;
  initialized_ = true; lastSample_ = now; lastMagnitude_ = magnitude;
  if (baseline) candidate_ = false;
  if (jerk > 35 && (!toggled_ || uint32_t(now - lastToggle_) >= 600)) {
   toggled_ = true; lastToggle_ = now; armed_ = false; candidate_ = false;
   return Command::Toggle;
  }
  if (toggled_ && uint32_t(now - lastToggle_) < 600) return Command::None;
  if (std::fabs(x) < 2.5f) { armed_ = true; candidate_ = false; return Command::None; }
  if (!armed_) return Command::None;
  const int direction = x > 5 ? 1 : (x < -5 ? -1 : 0);
  if (!direction) { candidate_ = false; return Command::None; }
  if (!candidate_ || direction != direction_) {
   candidate_ = true; direction_ = direction; tiltStart_ = now;
   return Command::None;
  }
  if (uint32_t(now - tiltStart_) < 150) return Command::None;
  armed_ = false; candidate_ = false;
  return direction > 0 ? Command::Color : Command::White;
 }
};
struct Light {
 bool on = false;
 bool white = false;
 uint8_t color = 0;
 uint8_t level = 0;
 bool apply(Command command) {
  switch(command) {
   case Command::Color: color = (color + 1) % 6; white = false; break;
   case Command::White: level = (level + 1) % 4; white = true; break;
   case Command::Toggle: on = !on; break;
   default: return false;
  }
  return true;
 }
};
}
