# Gesture Controlled Car

This project implements a gesture-controlled car using an **nRF24L01 wireless module** and an **MPU6050 accelerometer/gyroscope sensor**. The car can be controlled wirelessly by hand gestures detected by the MPU6050 sensor mounted on the transmitter (e.g., worn on hand or placed on a remote controller).

---

## Features

- Wireless control of car movement using hand gestures.
- Uses **MPU6050** sensor to detect tilt gestures (forward, backward, left, right).
- **nRF24L01** radio modules for communication between transmitter and receiver.
- Motor driver control via Arduino PWM pins to drive two DC motors.
- Simple commands sent as numeric codes for direction control.

---

## Components Needed

### Hardware

- 2 x Arduino boards (e.g., Arduino Uno)
- 1 x MPU6050 accelerometer/gyroscope sensor
- 2 x nRF24L01 wireless transceiver modules
- 2 x DC motors with motor driver circuit (e.g., L298N or equivalent)
- Jumper wires and power supply
- Chassis for the car with wheels

---

## System Overview

### Transmitter

- Reads accelerometer values from MPU6050 sensor.
- Interprets tilt gestures to decide movement commands:
  - Forward, Backward, Left, Right.
- Sends commands wirelessly to receiver via nRF24L01.

### Receiver

- Receives commands wirelessly.
- Controls the motor driver pins to move the car accordingly.
- Implements PWM speed control for motors (currently fixed speed).

---

## Wiring Summary

### Transmitter

- MPU6050 connected via I2C (SDA, SCL to Arduino SDA/SCL pins).
- nRF24L01 connected to SPI pins + CE (pin 7) and CSN (pin 8).
- Arduino powered and connected via USB or battery.

### Receiver

- nRF24L01 connected to SPI pins + CE (pin 8) and CSN (pin 7).
- Motor driver connected to Arduino pins:
  - IN1 -> pin 2
  - IN2 -> pin 3
  - IN3 -> pin 4
  - IN4 -> pin 5
  - Speed control PWM pins -> 9 and 10
- Motors connected to motor driver output.
- Power motors with appropriate power source.

---

## Code Explanation

### Transmitter Code

- Uses **MPU6050 library** to read accelerometer data.
- Checks tilt values on X (ax) and Y (ay) axes to determine direction:
  - Large negative `ay` → Forward
  - Large positive `ay` → Backward
  - Large negative `ax` → Right
  - Large positive `ax` → Left
- Sends a command byte (1 to 4) corresponding to the direction via nRF24L01.
- Command 0 means no movement.
- Uses a fixed delay of 500ms between transmissions.

### Receiver Code

- Listens for incoming command bytes via nRF24L01.
- Based on received command, sets motor driver pins to move the car:
  - 1 = forward
  - 2 = backward
  - 3 = left
  - 4 = right
- Sets both motors to full speed (PWM value 255).
- Prints received command and movement direction on Serial Monitor.

---

## How to Use

1. **Setup hardware** according to wiring diagram above.
2. **Upload transmitter code** to the Arduino connected to MPU6050 and nRF24L01.
3. **Upload receiver code** to the Arduino connected to motor driver and nRF24L01.
4. Power on both Arduinos.
5. Tilt the transmitter unit in different directions to control the car.
6. Observe car moving in the corresponding direction wirelessly.

---

## Potential Improvements

- Implement speed control based on tilt intensity (currently speed fixed).
- Add calibration and filtering for more accurate gesture detection.
- Use interrupts or better timing to reduce delay and improve responsiveness.
- Add safety stop or timeout if communication lost.
- Enclose components in a compact casing for portability.

---

## References

- [MPU6050 Arduino Library](https://github.com/jrowberg/i2cdevlib/tree/master/Arduino/MPU6050)
- [nRF24L01 Arduino Library (RF24)](https://github.com/nRF24/RF24)

---

## Author

**Tarun Parthiban**  
Prefinal Year, Computer Science Engineering (AI & Robotics)  
VIT Chennai  

---

## License

This project is open source and free to use for educational and hobby purposes.

---
