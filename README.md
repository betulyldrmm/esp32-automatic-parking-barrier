# ESP32 Automatic Parking Barrier System

<p align="center">
  <img src="images/project.jpg" width="750">
</p>

An automatic parking barrier system developed using an **ESP32 Development Board**, **HC-SR04 Ultrasonic Sensor**, **SG90 Servo Motor**, and **SSD1306 OLED Display**.

The system detects approaching vehicles using an ultrasonic sensor and automatically opens the barrier. After the vehicle passes, the barrier closes after a predefined delay.

This project demonstrates basic embedded systems concepts such as sensor integration, servo motor control, OLED communication, GPIO management, and real-time automation using ESP32.

---

# Features

- Vehicle detection using the HC-SR04 ultrasonic sensor
- Automatic barrier control with SG90 servo motor
- OLED display for welcome messages
- Automatic barrier closing after vehicle passage
- Real-time distance measurement
- Voltage divider protection for ESP32 GPIO input
- Simple and beginner-friendly embedded systems project

---

# Hardware Components

- ESP32 Development Board
- HC-SR04 Ultrasonic Distance Sensor
- SG90 Servo Motor
- SSD1306 OLED Display
- Breadboard
- Jumper Wires
- Resistors (Voltage Divider)



---

# Pin Connections

| Component | ESP32 Pin |
|-----------|-----------|
| HC-SR04 TRIG | GPIO 33 |
| HC-SR04 ECHO | GPIO 34 (via Voltage Divider) |
| SG90 Servo Signal | GPIO 13 |
| OLED SDA | GPIO 26 |
| OLED SCL | GPIO 25 |

---

# Required Libraries

Install the following libraries using the Arduino IDE Library Manager.

- ESP32Servo
- Adafruit SSD1306
- Adafruit GFX

> **Note:** `Wire.h` is included with the Arduino IDE.

---

# How It Works

1. The HC-SR04 continuously measures the distance in front of the barrier.
2. When a vehicle is detected within **15 cm**, the servo motor opens the barrier.
3. The OLED screen displays a welcome message.
4. The system keeps updating the last detection time while the vehicle is present.
5. Three seconds after the last detection, the barrier automatically closes.

---

# Project Parameters

The following values can be easily modified inside the source code.

```cpp
const int ACILMA_MESAFESI = 15;
const int KAPALI_ACI = 90;
const int ACIK_ACI = 0;
const int BEKLEME_SURESI = 3000;
```

| Parameter | Description |
|-----------|-------------|
| ACILMA_MESAFESI | Distance threshold for opening the barrier |
| KAPALI_ACI | Servo angle when the barrier is closed |
| ACIK_ACI | Servo angle when the barrier is open |
| BEKLEME_SURESI | Delay before automatically closing the barrier |

---

# Project Images

## Barrier Closed

<img width="1600" height="1200" alt="barrier-close jpg" src="https://github.com/user-attachments/assets/17ac6c5c-310f-4bea-986e-20094edef79b" />

## Barrier Open

<img width="1600" height="1200" alt="barrier-open jpg" src="https://github.com/user-attachments/assets/57c2b101-db28-404a-a16a-1aa8390cd679" />


---

# Folder Structure

```
esp32-automatic-parking-barrier
│
├── images
│
│   ├── barrier-open.jpg
│   └── barrier-close.jpg
│
├── esp32_automatic_parking_barrier.ino
└── README.md
```

---

# Future Improvements

- Vehicle counting
- RFID access control
- Parking space monitoring
- Mobile application integration
- Web dashboard
- IoT support using MQTT
- Cloud-based parking management

---


# License

This project is provided for educational and learning purposes.

If you find this project useful, feel free to fork it and build your own improvements.
