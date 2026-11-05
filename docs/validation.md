# Results and validation

## What the group report states

Sections 4–5 describe successful recognition of tilt-right, tilt-left, and sudden-motion gestures; decoding of commands 1, 2, and 3; and corresponding color, white-level, and power-toggle responses. The discussion reports latency under 100 ms and wider angular reception using four IR receivers per lantern.

The report attributes an integration failure to interference from the step-up booster and describes removing the booster. No electrical measurements are supplied to independently establish that diagnosis.

## Evidence limits

No firmware execution, hardware test, or independent performance measurement was conducted while preparing this repository. The supplied report does not include raw latency traces, timing methodology, trial counts, gesture confusion rates, reception-angle measurements, range tests, or battery-life measurements. Avoid claims of quantified reliability, full 360-degree coverage, guaranteed latency, or a specific operating range.

## Recommended future checks — not yet performed

1. Record board variants, module part numbers, final wiring, firmware revision, dependencies, and supply conditions.
2. Exercise each gesture and neutral input; record expected and actual behavior for all three lanterns over repeated trials.
3. Check repeated gestures and held tilts for unintended repeated toggles or changes.
4. Measure motion-to-light latency with a documented timing method and report sample count and distribution.
5. Test reception across distances, angles, ambient lighting conditions, and obstructions; record misses per trial.
6. Compare the documented power arrangements only after verifying their electrical suitability; record supply behavior and interference evidence.
7. Measure runtime and false triggers under ordinary arm motion.

Retain test logs separately from the narrative report so future claims can be traced to measurements.
