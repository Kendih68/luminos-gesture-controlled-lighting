# Source provenance and open questions

## Source used

Primary source: the seven-page uploaded PDF `Proj1_Report_Group1.docx.pdf`, titled *Luminos: a Doctor Strange Inspired Device*. All seven pages were read and visually inspected during documentation preparation on 5 November 2026. The report is included at `report/luminos-project-report.pdf` following Mathas's confirmation of group permission on 5 November 2026.

Page references for verification:

- Page 1: title, author list, affiliation, abstract, main components.
- Page 2: one wearable and three lanterns; four receivers per lantern; 38 kHz signaling; 16-pixel rings; I²C; motion processing; IRremote; D15 reference.
- Page 3: Table 1 gesture/command mapping; block diagram; wearable design-stage circuit.
- Pages 3–4: wearable enclosure and base design.
- Pages 4–5: lantern circuit and mechanical design; command decoding and visual response.
- Page 6: transistor and booster removal, direct-to-Vin statement, interference account, reported sub-100-ms latency, limitations and proposed development.
- Page 7: proposed software/hardware extensions and acknowledgments.

Individual contribution scope comes from the prior project conversation supplied with this request, rather than an author-by-author breakdown in the report. Mathas confirmed his author identity and approved the proposed repository name in this chat.

## Ambiguities preserved

- Figure 1 is labeled IR-WiFi and shows a host/API path. The narrative supports IR gesture control; there is insufficient evidence to claim a working Wi-Fi interface or hosted application.
- The early wearable schematic includes a booster and transistor; later sections describe removing them. A final schematic is needed.
- D15 and receiver connection wording do not establish a verified pin-level wiring guide.
- The report uses both ring and strip terminology. The component/design descriptions specify 16-pixel NeoPixel rings.
- Latency is reported without measurement details; it is not a benchmark reproduced for this repository.
- Proposed filtering, additional gestures, animations, interrupt-based operation, and PCB integration are future work.

## Materials unavailable

No original firmware, editable CAD, standalone schematic source, build configuration, prototype photographs/video, or measurement logs were provided. Figures embedded in the PDF do not establish the availability of the original design files.
