// Host tests for gesture detection and lighting state.
#include "logic.h"
#include <cassert>
#include <cmath>
#include <cstdio>
using namespace luminos;
int main() {
 Gestures g;
 assert(g.update(0, 9.81f, 0) == Command::None);
 assert(g.update(6, 9.81f, 20) == Command::None);
 assert(g.update(6, 9.81f, 169) == Command::None);
 assert(g.update(6, 9.81f, 170) == Command::Color);
 assert(g.update(6, 9.81f, 400) == Command::None);
 assert(g.update(-6, 9.81f, 600) == Command::None); // neutral required
 g.update(0, 9.81f, 620);
 g.update(-6, 9.81f, 640);
 assert(g.update(-6, 9.81f, 790) == Command::White);
 Gestures rapid;
 Light rapidLight;
 rapid.update(0, 9.81f, 0);
 rapid.update(6, 9.81f, 20);
 auto color = rapid.update(6, 9.81f, 170);
 assert(color == Command::Color && rapidLight.apply(color));
 auto toggle = rapid.update(0, 16, 190);
 assert(toggle == Command::Toggle && rapidLight.apply(toggle) && rapidLight.on);
 Gestures shake;
 shake.update(0, 9.81f, 0);
 assert(shake.update(0, 16, 20) == Command::Toggle);
 assert(shake.update(0, 9.81f, 40) == Command::None);
 assert(shake.update(0, 16, 60) == Command::None);
 shake.update(0, 9.81f, 620);
 assert(shake.update(0, 16, 640) == Command::Toggle);
 Gestures invalid;
 invalid.update(0, 9.81f, 0);
 assert(invalid.update(NAN, 10, 20) == Command::None);
 assert(invalid.update(0, INFINITY, 40) == Command::None);
 assert(invalid.update(0, 16, 1000) == Command::None); // gap resets baseline
 Gestures wrap;
 wrap.update(0, 9.81f, UINT32_MAX - 100);
 wrap.update(6, 9.81f, UINT32_MAX - 80);
 assert(wrap.update(6, 9.81f, 70) == Command::Color);
 Gestures noise;
 noise.update(0, 9.81f, 0);
 noise.update(6, 9.81f, 20);
 noise.update(0, 9.81f, 100);
 assert(noise.update(6, 9.81f, 180) == Command::None);
 assert(noise.update(6, 9.81f, 330) == Command::Color);
 Light light;
 assert(!light.on);
 assert(!light.apply(Command::None));
 assert(!light.apply(static_cast<Command>(99)));
 assert(light.apply(Command::Toggle) && light.on);
 assert(light.apply(Command::White) && light.white && light.level == 1);
 assert(light.apply(Command::Color) && !light.white && light.color == 1);
 assert(light.apply(Command::Toggle) && !light.on);
 for(int i=0;i<5;++i) light.apply(Command::Color);
 assert(light.color == 0 && !light.on);
 for(int i=0;i<3;++i) light.apply(Command::White);
 assert(light.level == 0 && light.white);
 std::puts("Gesture and lighting behavior checks passed.");
}
