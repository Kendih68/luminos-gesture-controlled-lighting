# System and hardware notes

This document summarizes the report; it is not a verified wiring or assembly guide.

## Architecture

One wearable controller transmits commands to three lanterns. The wearable uses an ESP32, MPU6050, and IR emitter. Each lantern uses an ESP32, four IR receivers, and a NeoPixel ring with 16 addressable LEDs. The report names the IRremote library for decoding, but gives no library version or complete build environment.

Gesture recognition uses x-axis acceleration for tilt and changes in total acceleration for sudden movement. Threshold values, sampling rate, filtering, cooldown behavior, and the original implementation are unavailable.

## Components described in the report

The wearable design section lists a 3.7 V, 1000 mAh lithium battery, a single-cell protection module, slide switch, MT3608 step-up booster, 940 nm IR LED, 2N2222 transistor, resistor, and capacitor, alongside the ESP32 and MPU6050. This is a description of the design-stage circuit, not a confirmed final bill of materials.

Later results say that the booster and NPN transistors were removed to address interference and improve compactness. The report says the battery was then connected directly to ESP32 Vin. That is a historical implementation statement; the exact board, operating-voltage requirements, protection arrangement, and final emitter circuit must be verified before reproducing it.

The lantern component list specifies four IR receiver modules and a NeoPixel ring per ESP32. Exact module part numbers, board revisions, lantern power supply details, component ratings, and a final quantity-checked bill of materials are not supplied.

## Electrical questions to resolve

- Confirm the final wearable schematic after the reported booster and transistor removals.
- Confirm ESP32 board variants, input-voltage requirements, battery protection, and actual power wiring.
- Confirm final IR emitter current limiting and drive method.
- Resolve receiver interconnection: the report references D15 for all receivers, while other wording describes individual digital inputs. Do not infer a safe multi-output connection from this summary.
- Verify the MPU6050, emitter, receiver, and LED pin mapping from original files and the assembled hardware.
- Confirm NEC address, command encoding, repeat behavior, and the exact IRremote version.

## Mechanical design

The wearable consists of an enclosure and a base. Reported features include screw mounting posts, an IR transmitter opening and mounting plate, internal compartments, and strap slots in the base.

The lantern consists of a threaded head and base. Side openings expose receivers, and an internal cantilever support holds a receiver module in position.

The report contains CAD illustrations but no editable CAD models, print-ready exports, verified dimensions, material specifications, tolerances, or manufacturing instructions. Do not treat the illustrations as a complete fabrication package.

## Before a build release

Obtain original firmware and CAD files, resolve the final schematic, document dependencies and configuration, and verify one complete wearable-to-lantern build before writing installation or assembly instructions.
