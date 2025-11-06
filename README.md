# D3AJ – Mine Detector (Arduino Mega)

Wheeled mobile robot to detect metal (mines) using a **Metal Detector sensor**, controlled over **PS2 Wireless** gamepad.  
Actuation via **two L298N** drivers (4 DC motors) + **3× MG996R** servos for the arm.

## Hardware (Bill of Materials)
- **MCU:** Arduino Mega 2560
- **Motor Drivers:** 2× L298N Dual H-Bridge
- **Motors:** 4× DC gear motors (3–6V)
- **Servos:** 3× MG996R (metal gear)
- **Controller:** PS2 Wireless 2.4 GHz gamepad + receiver
- **Sensor:** Metal Detector module (signal → analog input)
- **Power:** Battery pack (7.4–12V preferred for motors via L298N) + 5–6V stable for servos)
  
  ## Suggested Pin Map (edit to match your wiring)
**L298N (Left driver)**  
- ENA → D5 (PWM)  
- IN1 → D6, IN2 → D7  
- IN3 → D8, IN4 → D9  
- ENB → D10 (PWM)  

**L298N (Right driver)**  
- ENA → D11 (PWM)  
- IN1 → D12, IN2 → D13  
- IN3 → D22, IN4 → D23  
- ENB → D24 (PWM)

**Servos (MG996R)**  
- Shoulder → D3  
- Elbow → D4  
- Wrist  → D25  


**PS2 Wireless Receiver** (Using the PS2X library) 
- DATA → D50 (MISO)  
- CMD  → D51 (MOSI)  
- ATT  → D52 (SS)  
- CLK  → D53 (SCK)  


**Metal Detector Sensor**  
- Signal → A0  
- VCC → 5V (According to the model) 
- GND → GND

## Software
- Arduino IDE 2.x  
- **Libraries:**
  - `PS2X_lib` to control the PS2 controller (Or its alternative) 
  - `Servo.h` (For servos)

## How to Run
1. Open `firmware/D3AJ_MineDetector.ino` in the Arduino IDE.

2. Tools → Board: **Arduino Mega 2560** + Port

3. Install the required libraries.

4. Upload.

5. Connect the PS2 receiver and power on the controller; test the wheel and controller movement and metal detection.

## Basic Tests
- **Motors:** Try each channel on the L298N (front/back).
- **Servos:** Sweep 0↔180° for each joint.  
- **Detector:** Read `analogRead(A0)` via Serial Monitor and check for a change in value near the metal

## Power & Safety
## ⚠️ Power & Safety
- Servos require high current; do not power them from the Arduino's 5V supply.

- Disconnect the motor power supply from the logic power supply, using a common GND.

- Add a diode or TVS (TVS) if possible to protect the sensor from electrical noise
  
## 🖼 Media
https://drive.google.com/drive/folders/1zkOhFIgYY8R6_d2tlRjzmbzwSlgLGHVp?usp=sharing. 
