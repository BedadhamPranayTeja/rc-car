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

## 💻 Software Setup (Detailed Guide)

### 1. Install Arduino IDE
If you haven't already, download and install the legacy **Arduino IDE** or the new **IDE 2.0** from the [official website](https://www.arduino.cc/en/software).

### 2. Install ESP8266 Board Support
The Arduino IDE doesn't know about ESP8266 by default. We need to teach it:
1.  Open Arduino IDE.
2.  Go to **File** > **Preferences** (Windows/Linux) or **Arduino IDE** > **Settings** (macOS).
3.  Find the field named **"Additional Boards Manager URLs"**.
4.  Paste this URL into the box:
    `http://arduino.esp8266.com/stable/package_esp8266com_index.json`
    *(If there is already text there, add a comma `,` before pasting this new link).*
5.  Click **OK**.
6.  Go to **Tools** > **Board** > **Boards Manager...**
7.  In the search bar, type `esp8266`.
8.  Find **"esp8266 by ESP8266 Community"** and click **Install**.

### 3. Install USB Drivers (Critical Step)
Most affordable ESP8266 boards (NodeMCU / D1 Mini) use the **CH340G** USB-to-Serial chip. Windows/Mac might not recognize it automatically.
*   **Check**: Plug in your board. If you don't see a new COM port in `Tools > Port`, you likely need the driver.
*   **Solution**: Download and install the **CH340 Driver** (Google "CH340 driver" or find a reputable source).
*   *Note: Some high-quality boards use the CP2102 chip, which usually works automatically.*

### 4. Configure & Upload Code
1.  Open `rc_car_esp8266.ino` from this folder in Arduino IDE.
2.  Connect your ESP8266 to your computer with a **Data-capable MicroUSB cable** (some cables are charge-only!).
3.  **Select Board**: Go to `Tools > Board > ESP8266 Boards` and choose:
    *   **NodeMCU 1.0 (ESP-12E Module)** (Most common for NodeMCU)
    *   **LOLIN(WEMOS) D1 R2 & mini** (If using D1 Mini)
    *   *If unsure, Generic ESP8266 Module often works but specific is better.*
4.  **Select Port**: Go to `Tools > Port` and pick the new COM port that appeared (e.g., `COM3`, `COM5`, `/dev/cu.usbserial...`).
5.  **Upload**: Click the **Arrow Icon (➜)** in the top-left corner.
    *   The IDE will compile the code and transfer it to the board.
    *   Wait for **"Done uploading"** message at the bottom.

### ⚠️ Troubleshooting Uploads
If you see `Connecting........_____.....` and it fails:
1.  **Hold** the **FLASH** button on your ESP8266 board.
2.  While holding FLASH, press and release the **RST** (Reset) button once.
3.  Wait until the upload starts in the IDE, then release the **FLASH** button.

## 🎮 How to Drive

1.  Turn on the Power Bank.
2.  On your phone, search for WiFi networks.
3.  Connect to **`RC-Car-ESP`** (Password: `12345678`).
4.  Open a browser (Chrome/Safari) and go to: **`http://192.168.4.1`**
5.  Use the on-screen buttons to drive!
