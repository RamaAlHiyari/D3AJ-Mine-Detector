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
- **Power:** Battery pack (مفضل 7.4–12V للمحركات عبر L298N) + 5–6V مستقرة للسيرفوهات
  
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
> *غذّي السيرفوهات من منبع 5–6V منفصل قادر على 2–3A على الأقل، ووصّلي **GND مشترك** مع الأردوينو.*

**PS2 Wireless Receiver** (Using the PS2X library) 
- DATA → D50 (MISO)  
- CMD  → D51 (MOSI)  
- ATT  → D52 (SS)  
- CLK  → D53 (SCK)  
> يمكن تغيير الأرجل في الكود لو أردتِ.

**Metal Detector Sensor**  
- Signal → A0  
- VCC → 5V (According to the model) 
- GND → GND

## Software
- Arduino IDE 2.x  
- **Libraries:**
  - `PS2X_lib` to control the PS2 controller (Or its alternative) 
  - `Servo.h` (For servos)
  - (أضف أي مكتبات أخرى تستخدمينها)

## How to Run
1. افتحي `firmware/D3AJ_MineDetector.ino` في Arduino IDE.  
2. Tools → Board: **Arduino Mega 2560** + Port   
3. ثبتي المكتبات المطلوبة.  
4. Upload.  
5. وصّلي مستقبل الـPS2 وشغّلي الذراع؛ جربي حركة العجلات والذراع وكشف المعدن.

## Basic Tests
- **Motors:** Try each channel on the L298N (front/back).
- **Servos:** Sweep 0↔180° for each joint.  
- **Detector:** Read `analogRead(A0)` via Serial Monitor and check for a change in value near the metal

## Power & Safety
## ⚠️ Power & Safety
- Servos require high current; do not power them from the Arduino's 5V supply.

- Disconnect the motor power supply from the logic power supply, using a common GND.

- Add a diode or TVS (TVS) if possible to protect the sensor from electrical noise.
- السيرفوهات تحتاج تيار عالي؛ لا تغذّيها من 5V الخاص بالأردوينو. 
- افصل تغذية المحركات عن تغذية المنطق، مع **GND مشترك**.  
- أضف **Diode** أو **TVS** إن أمكن لحماية الحساس من الضوضاء الكهربائي
## 🖼 Media
https://drive.google.com/drive/folders/1zkOhFIgYY8R6_d2tlRjzmbzwSlgLGHVp?usp=sharing
- أضف صور الروبوت في `docs/.

#ؤخيث 
