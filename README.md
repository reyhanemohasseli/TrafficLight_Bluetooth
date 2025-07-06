# 🚦 Bluetooth-Controlled Traffic Light with ESP32

A smart traffic light system built using an ESP32 microcontroller, controlled wirelessly over Bluetooth from a iphone. This project demonstrates real-time switching of red, yellow, and green traffic lights via simple commands sent over Bluetooth.

# Project Overview

This project contains:
- A custom PCB and schematic design
- ESP32-based control logic
- Bluetooth Serial communication
- Arduino-compatible firmware
- LED light sequencing for red, yellow, and green signals

# How to Use
Upload the code to your ESP32 using Arduino IDE.
Pair your iphone with the ESP32 via Bluetooth (pair with the device named "myESP32").
Use an iOS app that supports Bluetooth Serial communication, such as LightBlue or Bluetooth Serial Controller.
Send single-letter commands (R, Y, G, O) to control the lights.
