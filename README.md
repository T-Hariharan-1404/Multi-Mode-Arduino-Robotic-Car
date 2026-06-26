# Multi-Mode-Arduino-Robotic-Car


A multifunctional robotic car built using **Arduino Uno** that combines **Bluetooth control**, **voice control**, and **automatic obstacle avoidance** into a single embedded system.

The robot can be manually controlled using the **Arduino Bluetooth Controller** mobile application, respond to voice commands transmitted via Bluetooth, or autonomously detect and avoid obstacles using an ultrasonic sensor.

---

##  Overview

This project demonstrates the integration of wireless communication, embedded programming, motor control, and sensor-based navigation. It provides multiple operating modes that allow users to manually drive the robot or let it navigate independently in obstacle avoidance mode.

The project is designed as an educational platform for learning Arduino-based robotics and embedded systems.

---

##  Features

-  Bluetooth-controlled navigation
-  Voice control through Bluetooth
-  Autonomous obstacle avoidance
-  Multiple operating modes
-  Wireless communication
-  Real-time response
-  Differential motor control
-  Portable battery-powered design

---

##  Hardware Components

- Arduino Uno
- HC-05 Bluetooth Module
- L298N Motor Driver
- HC-SR04 Ultrasonic Sensor
- Servo Motor
- DC Gear Motors
- Robot Chassis
- Wheels
- Battery Pack
- Jumper Wires

---

##  Software

- Arduino IDE
- Arduino Bluetooth Controller App

---

##  Operating Modes

###  Bluetooth Mode

The robot is controlled manually using the Arduino Bluetooth Controller application.

Available controls include:

- Forward
- Backward
- Left
- Right
- Stop

---

###  Voice Mode

Voice commands are recognized by the smartphone through the **Arduino Bluetooth Controller App** and transmitted to the HC-05 Bluetooth module.

Supported commands:

- Forward
- Back
- Left
- Right
- Stop

> Voice recognition is performed by the mobile application, while the Arduino executes the received commands.

---

###  Obstacle Avoidance Mode

The ultrasonic sensor continuously monitors the path ahead.

When an obstacle is detected, the robot automatically changes direction and continues moving safely without user intervention.

---


##  Getting Started

1. Assemble the hardware.
2. Upload the Arduino sketch.
3. Pair your smartphone with the HC-05 module.
4. Open the Arduino Bluetooth Controller App.
5. Select Bluetooth or Voice mode.
6. Enjoy manual control or switch to obstacle avoidance mode.

---

##  Learning Outcomes

- Embedded Systems
- Arduino Programming
- Bluetooth Communication
- Mobile Application Integration
- Motor Driver Interfacing
- Ultrasonic Sensor Interfacing
- Robotics Fundamentals

---

##  Future Improvements

- ESP32 Wi-Fi Control
- Camera Streaming
- IoT Dashboard
- GPS Navigation
- Line Following
- AI-Based Object Recognition

---
