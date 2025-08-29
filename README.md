# Robotic Arm Innovation

A vision-guided robotic arm system for automated pick-and-place tasks.

## My Contributions
- Programmed the ESP32 microcontroller to control robotic arm motors.
- Developed a Python script using YOLO + OpenCV for object detection.
- Established communication between the vision system (PC) and ESP32 via WebSocket/Serial.
- Implemented basic inverse kinematics and tested 3D-printed prototypes.

## Tech Stack
- Hardware: ESP32 microcontroller, 3D-printed robotic arm
- Software: Arduino IDE (C++/Embedded C), Python
- Computer Vision: YOLO, OpenCV
- Communication: WebSocket/Serial

## Files
- esp_robotic_arm_websocket.ino → ESP32 motor control logic
- robotic_arm_ws_communicaton.py → Python script for image detection and command transfer

## Note
This project demonstrates hardware-software integration for intelligent robotic arm control using computer vision.
