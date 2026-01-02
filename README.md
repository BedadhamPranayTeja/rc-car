# 🏎️ ESP8266 RC Car Project

This project turns a simple robot chassis into a WiFi-controlled RC car using an **ESP8266** (NodeMCU/D1 Mini), an **L298N Motor Driver**, and a **Power Bank**.

## 🛠️ Hardware Setup

### Components
*   **ESP8266 Module** (NodeMCU or D1 Mini)
*   **L298N Motor Driver**
*   **2x DC Gear Motors** + Wheels
*   **Power Bank** (USB 5V)
*   **Jumper Wires**

### 🔌 Wiring Diagram
Since you are using a **5V Power Bank**, we need to ensure the L298N gets power directly, and the ESP8266 is powered correctly.

#### 1. Power Connections
*   **Power Bank USB** -> **Split Cable** (or breadboard distribution):
    *   **5V Line** -> Connects to **L298N 12V** terminal (Yes, 5V into 12V input is fine for low voltage motors).
    *   **5V Line** -> Connects to **ESP8266 Vin** (or 5V pin).
    *   **GND Line** -> Connects to **L298N GND**.
    *   **GND Line** -> Connects to **ESP8266 GND**.
    *   **IMPORTANT**: Connect **L298N GND** to **ESP8266 GND** (Common Ground).

#### 2. Motor Connections
*   **Left Motor** -> Connects to **OUT1** and **OUT2** on L298N.
*   **Right Motor** -> Connects to **OUT3** and **OUT4** on L298N.

#### 3. Signal Connections (Pin Mapping)
| ESP8266 Pin | L298N Pin | Function |
| :--- | :--- | :--- |
| **D1 (GPIO 5)** | **IN1** | Left Motor Control |
| **D2 (GPIO 4)** | **IN2** | Left Motor Control |
| **D3 (GPIO 0)** | **IN3** | Right Motor Control |
| **D4 (GPIO 2)** | **IN4** | Right Motor Control |

> **Note**: Ensure the 5V jumper on the L298N is **ON** (if it has one) to enable the internal 5V regulator, though with 5V input it mostly just passes through logic voltage.

## 💻 Software Setup

1.  **Install ESP8266 Board Manager**:
    *   Open Arduino IDE -> Preferences.
    *   Add URL: `http://arduino.esp8266.com/stable/package_esp8266com_index.json`
    *   Tools -> Board -> Boards Manager -> Install `esp8266`.

2.  **Upload Code**:
    *   Open `rc_car_esp8266.ino`.
    *   Select Board: `NodeMCU 1.0 (ESP-12E Module)` (or whichever you have).
    *   Select Port and Click **Upload**.

## 🎮 How to Drive

1.  Turn on the Power Bank.
2.  On your phone, search for WiFi networks.
3.  Connect to **`RC-Car-ESP`** (Password: `12345678`).
4.  Open a browser (Chrome/Safari) and go to: **`http://192.168.4.1`**
5.  Use the on-screen buttons to drive!
