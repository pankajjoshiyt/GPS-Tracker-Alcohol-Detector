# GPS-Tracker-Alcohol-Detector
This project is a smart vehicle safety system designed to prevent drunk driving and improve vehicle security. It combines alcohol detection, GPS tracking, and engine locking features into one integrated embedded system.
# GPS Tracker & Alcohol Detector with Engine Locking System

This project is a smart vehicle safety system designed to prevent drunk driving and improve vehicle security. It combines alcohol detection, GPS tracking, and engine locking features into one integrated embedded system.

Click  on the link for visiting blog  https://www.theelectronicscreator.com/2026/04/gps-tracker-alcohol-detector-with.html

## Features
- Detects alcohol level using alcohol sensor
- Automatically locks/disables engine when alcohol is detected above threshold
- Tracks real-time vehicle location using GPS module
- Displays system status on LCD
- Alerts user through buzzer/LED indications
- Enhances road safety and accident prevention

## Components Used
- Arduino / Microcontroller
- Alcohol Sensor
- GPS Module
- Relay Module
- LCD Display
- Buzzer / LEDs
- Power Supply

## Applications
- Smart vehicle safety
- Anti-drunk driving systems
- Fleet monitoring and tracking
- Automotive security solutions


## Circuit Connections

### Alcohol Sensor
- VCC → 5V
- GND → GND
- Analog Output → A0

### GPS Module
- VCC → 5V
- GND → GND
- TX → Arduino Pin 2
- RX → Arduino Pin 3

### Relay Module (Engine Lock)
- VCC → 5V
- GND → GND
- IN → Arduino Pin 7

### Buzzer
- Positive → Arduino Pin 8
- Negative → GND

### Red LED
- Positive → Arduino Pin 9
- Negative → GND (through resistor)

### Green LED
- Positive → Arduino Pin 10
- Negative → GND (through resistor)

### LCD Display (I2C)
- VCC → 5V
- GND → GND
- SDA → A4
- SCL → A5


## Conclusion
This project demonstrates a smart and efficient vehicle safety solution by integrating GPS tracking, alcohol detection, and engine locking technology to help prevent drunk driving and improve road safety.

### Thank You for Visiting!
**Team The Electronics Creator**
