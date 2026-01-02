#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// ====================================================================================
// CONFIGURATION
// ====================================================================================
const char *ssid = "RC-Car-ESP"; // Name of the WiFi network created by the car
const char *password = "12345678"; // Password (at least 8 characters)

// Motor A (Left)
const int IN1 = 5;  // D1
const int IN2 = 4;  // D2

// Motor B (Right)
const int IN3 = 0;  // D3
const int IN4 = 2;  // D4

// ====================================================================================
// WEB INTERFACE (HTML)
// ====================================================================================
const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1.0, user-scalable=no">
  <title>RC Car Controller</title>
  <style>
    body {
      font-family: 'Courier New', Courier, monospace;
      text-align: center;
      background-color: #1a1a1a;
      color: #00ff00;
      margin: 0;
      padding: 20px;
      user-select: none;
    }
    h1 { margin-bottom: 20px; }
    .container {
      display: flex;
      flex-direction: column;
      align-items: center;
      gap: 15px;
      margin-top: 50px;
    }
    .row { display: flex; gap: 15px; }
    button {
      width: 80px;
      height: 80px;
      font-size: 24px;
      font-weight: bold;
      color: #1a1a1a;
      background-color: #00ff00;
      border: none;
      border-radius: 10px;
      box-shadow: 0 4px #005500;
      active-background-color: #00cc00;
      active-box-shadow: 0 2px #005500;
      transform: translateY(0);
      transition: all 0.1s;
      cursor: pointer;
      -webkit-tap-highlight-color: transparent;
    }
    button:active {
      transform: translateY(4px);
      box-shadow: 0 0 #005500;
      background-color: #00cc00;
    }
    .stop-btn {
      background-color: #ff0000;
      color: white;
      box-shadow: 0 4px #550000;
      width: 100px;
    }
    .stop-btn:active {
      background-color: #cc0000;
      box-shadow: 0 0 #550000;
    }
    .status { margin-top: 20px; font-size: 14px; color: #888; }
  </style>
  <script>
    function send(action) {
      var xhr = new XMLHttpRequest();
      xhr.open("GET", "/" + action, true);
      xhr.send();
    }
    
    // Key listeners for keyboard control
    document.addEventListener('keydown', function(event) {
      if(event.repeat) return;
      if(event.key === "ArrowUp") send('F');
      if(event.key === "ArrowDown") send('B');
      if(event.key === "ArrowLeft") send('L');
      if(event.key === "ArrowRight") send('R');
      if(event.key === " ") send('S'); // Spacebar to stop
    });

    document.addEventListener('keyup', function(event) {
      // Optional: Stop on key release? usually better to keep moving until 'stop' pressed or specific logic
      // For this simple version, we stop when keys are released to mimic "hold to drive"
      send('S');
    });
  </script>
</head>
<body>
  <h1>RC BOT V1</h1>
  <div class="container">
    <div class="row">
      <button onmousedown="send('F')" ontouchstart="send('F')" onmouseup="send('S')" ontouchend="send('S')">▲</button>
    </div>
    <div class="row">
      <button onmousedown="send('L')" ontouchstart="send('L')" onmouseup="send('S')" ontouchend="send('S')">◀</button>
      <button class="stop-btn" onclick="send('S')">STOP</button>
      <button onmousedown="send('R')" ontouchstart="send('R')" onmouseup="send('S')" ontouchend="send('S')">▶</button>
    </div>
    <div class="row">
      <button onmousedown="send('B')" ontouchstart="send('B')" onmouseup="send('S')" ontouchend="send('S')">▼</button>
    </div>
  </div>
  <div class="status">Connect to WiFi: RC-Car-ESP<br>Go to 192.168.4.1</div>
</body>
</html>
)=====";

ESP8266WebServer server(80);

void handleRoot() {
  server.send(200, "text/html", MAIN_page);
}

// ====================================================================================
// MOVEMENT FUNCTIONS
// ====================================================================================
void stopBot() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  Serial.println("STOP");
}

void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("FORWARD");
}

void moveBackward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("BACKWARD");
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH); // Left moves back
  digitalWrite(IN3, HIGH); // Right moves fwd
  digitalWrite(IN4, LOW);
  Serial.println("LEFT");
}

void turnRight() {
  digitalWrite(IN1, HIGH); // Left moves fwd
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);  // Right moves back
  digitalWrite(IN4, HIGH);
  Serial.println("RIGHT");
}

void setup() {
  Serial.begin(115200);
  
  // Set Motor Pins as Output
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Initial State: Stopped
  stopBot();

  // Setup WiFi Access Point
  Serial.println();
  Serial.print("Setting up Access Point...");
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  // Setup Web Server Routes
  server.on("/", handleRoot);
  server.on("/F", [](){ moveForward(); server.send(200, "text/plain", "OK"); });
  server.on("/B", [](){ moveBackward(); server.send(200, "text/plain", "OK"); });
  server.on("/L", [](){ turnLeft(); server.send(200, "text/plain", "OK"); });
  server.on("/R", [](){ turnRight(); server.send(200, "text/plain", "OK"); });
  server.on("/S", [](){ stopBot(); server.send(200, "text/plain", "OK"); });

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
