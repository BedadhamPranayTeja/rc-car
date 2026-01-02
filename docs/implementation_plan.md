# Implementation Plan - ESP8266 WiFi RC Car

We will turn your parts into a WiFi-controlled Robot Car. Since you are using a Power Bank (5V), we will use a specific wiring configuration to ensure the motors get enough power.

## Hardware Architecture

### Power Distribution (Critical for 5V Power Bank)
Standard BO motors run best at 6V-9V, but will work at 5V (slightly slower). The L298N driver drops ~1.5V-2V.
- **Power Bank USB 1** -> Connects to ESP8266 (MicroUSB) for power.
- **Power Bank USB 2 (or Split Cable)** -> Connects to L298N Driver.
    - **Positive (+)** -> Goes to L298N `12V` terminal AND `5V` terminal (Logic).
    - **Negative (-)** -> Goes to L298N `GND`.
    - **Common Ground** -> Ensure L298N `GND` connects to ESP8266 `GND`.

### Pin Mapping (ESP8266 NodeMCU/D1 Mini)
| Function | ESP8266 Pin (Code) | Wire To L298N |
| :--- | :--- | :--- |
| **Left Motor** | D1 (GPIO 5) | IN1 |
| **Left Motor** | D2 (GPIO 4) | IN2 |
| **Right Motor** | D3 (GPIO 0) | IN3 |
| **Right Motor** | D4 (GPIO 2) | IN4 |
| **Speed (Optional)**| (Software PWM) | ENA/ENB (Keep Jumpers on for max speed) |

## Software Design
We will write a single Arduino Sketch (`.ino`) that:
1.  **Creates a WiFi Access Point**: Named "RC-Car-ESP".
2.  **Hosts a Webserver**: Serves a simple HTML page with arrow keys.
3.  **Handles Requests**: processing `/F`, `/B`, `/L`, `/R`, `/S` to drive GPIO pins.

## Proposed Changes
### [NEW] `rc_car_esp8266.ino` in `c:/Users/prana/OneDrive/Desktop/robotics/low effort`
- Setup Code for AP Mode.
- HTML String (Proposing a dark mode UI).
- `handleRoot()` function.
- Motor control functions.

## Verification Plan
1.  **Compile & Upload**: User will upload via Arduino IDE.
2.  **Connect**: Phone connects to "RC-Car-ESP" WiFi.
3.  **Test**: Open `192.168.4.1` in browser and tap buttons.
