/*

       crocodile buggy 
 • our idea:
    wheeled mobile robot with metal detector sensor controlled by arm to detect metals (Mine)
 
 • Electronic parts
    1)  Arduino maga 1 
    2)  DC motors 4
    3)  wheels  8 
    4)  L298N motor driver 2
    5)  servo motor MG955 3 (180 degree)
    6)  metal detector 
    7)  programmable ps2 controller 
    8)  9V battery (Arduino)
    9)  5V battery (servos)
    10) 11.1V battery (DC motors) 
 
 • pins decumentation:
    • Servos:
        1) base servo : 13
        2) joint1 servo : 12
        3) joint2 servo : 11
        3) end effector : 10
    • Ps2 controllar:
        1) data : 9
        2) command : 8
        3) vibration : -
        4) GND : GND
        5) power : 3.3v or 5v
        6) attention : 7 
        7) clock : 6
        8) no connection : -
        9) Acknowledge : -
    • motors:
      • front: 
        1) Left:
          Enable : 5
          IN1 : 22
          IN2 : 24
        2) Right:
          Enable: 4
          IN3 : 26 
          IN4 : 28
     • Back:
        1)Right:
          Enable: 3
          IN1 : 36
          IN2 : 34
        4)Left:
         Enable: 2
          IN3 : 32
          IN4 : 30
    • sersor:
      V+ : 5v
      V- : GND
  • for movement: 
  1) arm
      Key       move   type
  PSB_PAD_UP    UP     Analog
  PSB_PAD_DOWN  DOWN   Analog
  PSB_PAD_LEFT  LEFT   Analog
  PSB_PAD_RIGHT RIGHT  Analog 
  2)motor movement
   Forword =>        X = 128  ,  Y = 0   
   Forword_left =>   X = 0    ,  Y = 0   
   Forword_Right =>  X = 255  ,  Y = 0   
   Left =>           X = 0    ,  Y = 128 
   Right =>          X = 255  ,  Y = 128  
   Backword =>       X = 128  ,  Y = 255  
   Backword_left =>  X = 0    ,  Y = 255 
   Backword_Right => X = 255  ,  Y = 255 
*/
#include <Servo.h>
#include <PS2X_lib.h>

class motor {
private:
  int speed;  //speed can be  between [0 , 255]
  byte first_pin, second_pin, Enable;
  // first_pin and second_pin will get the pins IN1 , IN2 , IN3 , IN4

public:
  //a contractor will help holding the pins for each motor
  motor(int speed, byte Enable, byte first_pin, byte second_pin) {
    this->speed = speed;
    this->Enable = Enable;
    this->first_pin = first_pin;
    this->second_pin = second_pin;
    pinMode(Enable, OUTPUT);
    pinMode(first_pin, OUTPUT);
    pinMode(second_pin, OUTPUT);
  }
  inline void speed_control(int speed) {
    this->speed = speed;
  }
  void Backword() {
    analogWrite(Enable, speed);
    digitalWrite(first_pin, HIGH);
    digitalWrite(second_pin, LOW);
  }



  void Forword() {
    analogWrite(Enable, speed);
    digitalWrite(first_pin, LOW);
    digitalWrite(second_pin, HIGH);
  }




  inline void stop() {
    analogWrite(Enable, 0);
  }
};
 
//motor(speed, Enable , first_pin, second_pin);
motor front_L(255,5, 26, 28), front_R(255,4, 22, 24);
motor back_L(255,3, 34, 36 ), back_R(255,  2, 30, 32);
//Servo
Servo base_servo, joint1_servo, joint2_servo, end_effector;
//controllr
PS2X ps2x;
byte error;

void stop_all() {
  front_L.stop();
  front_R.stop();
  back_L.stop();
  back_R.stop();
}
void setup() {
  Serial.begin(9600);
  //------------------------------------------------
  base_servo.attach(13);
  joint1_servo.attach(12);
  joint2_servo.attach(11);
  end_effector.attach(10);
  //------------------------------------------------
  //ps2x.config_gamepad(clock, command, attention, data, Pressures? Rumble?);
  error = ps2x.config_gamepad(6, 8, 7, 9, false, false);

  if (error == 0)
    Serial.println("Found Controller, configured successful.");
  else if (error == 1)
    Serial.println("No controller found.");
  else if (error == 2)
    Serial.println("Controller found but not accepting commands.");
  else if (error == 3)
    Serial.println("Controller refusing to enter Pressures mode, may not support it.");
}
void loop() {
  ps2x.read_gamepad();
  static byte base_angle = 90, joint1_angle = 90, joint2_angle = 90, end_effector_angle = 90;
  char *buffer = new char[10];


  if (ps2x.Button(PSB_START)) {
    base_angle = 90, joint1_angle = 90, joint2_angle = 90;
    base_servo.write(base_angle);
    delay(500);
    joint1_servo.write(joint1_angle);
    delay(500);
    joint2_servo.write(joint2_angle);
  } else if (ps2x.Button(PSB_PAD_DOWN)) {
    Serial.println("Arm UP J1!!");
    if (joint1_angle == 90)
      return;
    joint1_servo.write(joint1_angle -= 5);
    delay(50);
  } else if (ps2x.Button(PSB_PAD_UP)) {
    Serial.println("Arm DOWN J1!!");
    if (joint1_angle == 180)
      return;
    joint1_servo.write(joint1_angle += 5);
    delay(50);
  } else if (ps2x.Button(PSB_PAD_RIGHT)) {
    Serial.println("Arm Right!!");
    if (base_angle == 0)
      return;
    base_servo.write(base_angle -= 5);
    delay(50);
  } else if (ps2x.Button(PSB_PAD_LEFT)) {
    Serial.println("Arm LEFT!!");
    if (base_angle == 180)
      return;
    base_servo.write(base_angle += 5);
    delay(50);
  } else if (ps2x.Button(PSB_BLUE)) {
    Serial.println("Arm UP J2!!");
    if (joint2_angle == 90)
      return;
    joint2_servo.write(joint2_angle += 5);
    delay(50);
  } else if (ps2x.Button(PSB_GREEN)) {
    if (joint2_angle == 0)
      return;
    joint2_servo.write(joint2_angle -= 5);
    delay(50);
  } else if (ps2x.Button(PSB_PINK)) {
    if (end_effector_angle == 90)
      return;
    end_effector.write(end_effector_angle += 5);
    delay(50);
  } else if (ps2x.Button(PSB_RED)) {
    if (end_effector_angle == 0)
      return;
    end_effector.write(end_effector_angle -= 5);
    delay(50);
  } else if (ps2x.Button(PSB_R1)) {
    byte X = (ps2x.Analog(PSS_LX));
    byte Y = (ps2x.Analog(PSS_LY));
    sprintf(buffer, "X:%d Y:%d", X, Y);
    Serial.println(buffer);
    //------------------------------------------
    if (X == 128 && Y == 0) {  //Forword
      back_R.Forword();
      front_L.Forword();
      front_R.Forword();
      back_L.Forword();
     
      delay(50);
      stop_all();
    } else if (X == 0 && Y == 0) {  //  Forword Left
      front_L.Forword();
      front_R.Backword();
      back_L.Forword();
      back_R.Backword();
      delay(50);
      stop_all();
    } else if (X == 255 && Y == 0) {  //  Forword Right
      front_L.Backword();
      front_R.Forword();
      back_L.Backword();
      back_R.Forword();
      delay(50);
      stop_all();
    } else if (X == 0 && Y == 128) {  // Left
      front_L.Backword();
      front_R.Forword();
      back_L.Backword();
      back_R.Forword();
      delay(50);
      stop_all();
    } else if (X == 255 && Y == 128) {  // Right
      front_L.Forword();
      front_R.Backword();
      back_L.Forword();
      back_R.Backword();
      delay(50);
      stop_all();
    } else if (X == 128 && Y == 255) {  // Backword
      front_L.Backword();
      front_R.Backword();
      back_L.Backword();
      back_R.Backword();
      delay(50);
      stop_all();
    } else if (X == 0 && Y == 255) {  // Backword Left
      front_L.Backword();
      front_R.Forword();
      back_L.Backword();
      back_R.Forword();
      delay(50);
      stop_all();
    } else if (X == 255 && Y == 255) {  // Backword Right
      front_L.Forword();
      front_R.Backword();
      back_L.Forword();
      back_R.Backword();
      delay(50);
      stop_all();
    }
  }
  delay(50);
  stop_all();
  delete[] buffer;
}
