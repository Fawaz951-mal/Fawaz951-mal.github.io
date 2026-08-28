# 🚗 ESP32 4WD Wi-Fi RC Car

A simple **4WD remote-controlled car** built with an **ESP32**. The car creates its own Wi-Fi hotspot and provides a web-based controller that can be accessed from a phone, tablet, or computer.

The controller communicates with the ESP32 using **WebSockets**, providing responsive real-time movement control.

## ✨ Features

* 📡 ESP32 Wi-Fi Hotspot mode
* 🌐 Web-based remote controller
* ⚡ Real-time control using WebSockets
* ⬆️ Forward
* ⬇️ Backward
* ⬅️ Left
* ➡️ Right
* 🛑 Automatic stop when a button is released
* 🔌 Automatic motor stop when the controller disconnects
* 📱 Works from a phone, tablet, or computer

## 🧰 Hardware

* ESP32 development board
* 4WD car chassis
* 4 × DC motors
* Motor driver
* Battery pack
* Jumper wires

## 🔌 Motor Pin Configuration

| Motor Function | ESP32 GPIO |
| -------------- | ---------: |
| Left Forward   |    GPIO 27 |
| Left Backward  |    GPIO 26 |
| Right Forward  |    GPIO 25 |
| Right Backward |    GPIO 33 |

> **Note:** The right side motors are wired in the opposite direction, so their HIGH/LOW logic is reversed in the program.

## 📡 Wi-Fi Configuration

The ESP32 operates in **Access Point (Hotspot) mode**, so no external Wi-Fi router is required.

### Default Wi-Fi

```text
SSID: RC_CAR
Password: 12345678
```

> ⚠️ If this repository is public, consider changing the password before using the project.

## 🎮 Controls

| Button         | Action        |
| -------------- | ------------- |
| ⬆️             | Move Forward  |
| ⬇️             | Move Backward |
| ⬅️             | Turn Left     |
| ➡️             | Turn Right    |
| Release Button | Stop          |

The car only moves while the control button is being held.

## 🌐 How to Use

### 1. Upload the Program

Open `4wd_rc_car.ino` in the **Arduino IDE**.

Select your ESP32 board and the correct COM port, then upload the program.

### 2. Open Serial Monitor

After uploading:

1. Open the Arduino IDE Serial Monitor.
2. Set the baud rate to:

```text
115200
```

3. Reset the ESP32 if necessary.

The Serial Monitor will display the Wi-Fi network and IP address.

Example:

```text
BOOTING ESP32...
WiFi Hotspot Started
SSID: RC_CAR
IP Address: 192.168.4.1
HTTP Server Started
WebSocket Started
```

### 3. Connect to the Car

Using your phone, tablet, or computer:

1. Open Wi-Fi settings.
2. Connect to:

```text
RC_CAR
```

3. Enter the Wi-Fi password:

```text
12345678
```

### 4. Open the Controller

Open a web browser and enter the IP address shown in the Serial Monitor.

For example:

```text
http://192.168.4.1
```

You should see the RC car controller.

## ⚙️ Software

This project uses:

* Arduino IDE
* ESP32 Arduino framework
* `WiFi.h`
* `WebServer.h`
* `WebSocketsServer.h`
* HTML
* CSS
* JavaScript

## 🔄 Communication

The ESP32 runs two services:

### HTTP Server

The HTTP server runs on:

```text
Port 80
```

It serves the web-based controller.

### WebSocket Server

The WebSocket server runs on:

```text
Port 81
```

It handles real-time movement commands.

Commands sent by the controller:

```text
forward
backward
left
right
stop
```

## 🛑 Safety

The program includes an automatic stop function.

If the WebSocket connection is disconnected, the ESP32 executes:

```cpp
stop_car();
```

This prevents the car from continuing to drive if the controller loses connection.

## 📁 Project Structure

```text
esp32-4wd-rc-car/
│
├── 4wd_rc_car.ino
└── README.md
```

## 🚧 Future Improvements

Possible future features:

* 🎚️ Speed control
* 📷 ESP32-CAM video streaming
* 💡 LED headlights
* 🔋 Battery voltage monitoring
* 🕹️ Joystick controller
* 📱 Improved mobile interface
* 🔊 Buzzer/horn
* 🚨 Emergency stop button
* 📊 Car status information

## 📸 Project

Add photos or videos of the car here:

```text
Coming soon...
```

## 👨‍💻 Author

**Fawaz951-mal**

Built as an ESP32 4WD RC car project.

---

⭐ If you find this project useful, consider giving the repository a star!
