# D3AJ – Mine Detector (Arduino Mega)

A wheeled mobile robot that detects buried metal (mines) using a metal-detector sensor.  
It is driven by 4 DC motors through two L298N drivers and uses three MG996R servos for the arm 
Control is via a 2.4 GHz PS2 wireless gamepad


<img src="2.JPG" alt="D3AJ Mine Detector - Hero Image" width="900">



## Introduction
Landmine detection is very dangerous and still causes thousands of deaths each year.  
The **D3AJ Buggy** aims to reduce human risk by using a mobile robot that can scan, detect, and report danger zones in a safer way

## Hardware (Bill of Materials)
- **MCU:** Arduino Mega 2560  
- **Motor Drivers:** 2 × L298N dual H-bridge  
- **Motors:** 4 × DC gear motors (3–6 V)  
- **Servos:** 3 × MG996R (metal gear)  
- **Controller:** PS2 wireless gamepad + receiver  
- **Sensor:** Metal-detector module (analog output)  
- **Power:** 7.4–12 V battery for motors (via L298N), and a stable 5–6 V rail for servos

  ## Suggested Pin Map (edit to match your wiring)

**L298N – Left driver**
- ENA → D5 (PWM)  
- IN1 → D6, IN2 → D7  
- IN3 → D8, IN4 → D9  
- ENB → D10 (PWM)

**L298N – Right driver**
- ENA → D11 (PWM)  
- IN1 → D12, IN2 → D13  
- IN3 → D22, IN4 → D23  
- ENB → D24 (PWM)

**Servos (MG996R)**
- Shoulder → D3  
- Elbow → D4  
- Wrist  → D25

**PS2 Wireless Receiver** (PS2X library)
- DATA → D50 (MISO)  
- CMD  → D51 (MOSI)  
- ATT  → D52 (SS)  
- CLK  → D53 (SCK)

**Metal Detector Sensor**
- Signal → A0  
- VCC → 5 V (check your module)  
- GND → GND



<img src="3.JPG" alt="D3AJ Mine Detector - Hero Image" width="900">

## Software
- **Arduino IDE** 2.x  
- **Libraries:**
  - `PS2X_lib` (or alternative) for the PS2 controller
  - `Servo.h` for servo control

## How to Run
1. Open `firmware/D3AJ_MineDetector.ino` in Arduino IDE.  
2. **Tools → Board:** Arduino Mega 2560, select the correct **Port**.  
3. Install the required libraries.  
4. Upload the firmware.  
5. Connect the PS2 receiver, power the robot, and test wheels, servos, and detection.


## Basic Tests
- **Motors:** Test each L298N channel (forward/backward).  
- **Servos:** Sweep each joint from 0° to 180°.  
- **Detector:** `analogRead(A0)` in Serial Monitor; confirm the value changes near metal

 ## Power & Safety
- Servos draw high current: **do not** power them from the Arduino 5 V pin.  
- Separate motor power and logic power; **use common GND**.  
- Add protection (diodes/TVS) and decoupling to reduce electrical noise on the sensor line.  
- Field testing must follow local safety rules; this is a **training/prototyping** platform


### References
- Clearpath Robotics — Autonomous Demining Husky  
- IEEE Spectrum — Husky Robot for Landmine Detection  
- GeeksforGeeks — Encapsulation in C++  
- Siegwart, R., Nourbakhsh, I. R., & Scaramuzza, D. *Introduction to Autonomous Mobile Robots* (2nd ed.) Media

##  Design By RamaAlhiyari
Built with **parallel-link suspension** (coil spring + double wishbone) to improve stability, balance, and adaptability on rough terrain.  
The layout supports quick changes to sensors and motor modules
<img src="3dD3AJ.png" alt="D3AJ Mine Detector - Hero Image" width="900">

## Project Credits & Evolution
This project idea was created by **Rama Al-Hayari**, **Mohammad Ismail**, and **Julnar Radwan** 

**One month later, Rama Al-Hayari & Omar Moutaser extended the system** with **computer vision** and **AI** so the robot can work in a **hybrid mode** (semi-autonomous + manual via controller). The robot now:
- Displays detection results as **video overlays** on a screen, and  
- Sends the **danger location** to the expert via a **Telegram message**


 ##  D3AJ Post-Development Demo
[Download 10s MP4](Field-Test-10s.mp4)
  
## Media 
- Google Drive folder:  
  https://drive.google.com/drive/folders/1zkOhFIgYY8R6_d2tlRjzmbzwSlgLGHVp?usp=sharing


