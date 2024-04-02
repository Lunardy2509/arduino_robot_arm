#include <Servo.h>
#include <Wire.h>
// #include <SPI.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

Servo Servo_0;
Servo Servo_1;
Servo Servo_2;
Servo Servo_3;

int S0_pos, S1_pos, S2_pos, S3_pos, S4_pos, S5_pos, S6_pos, S7_pos;
int P_S0_pos, P_S1_pos, P_S2_pos, P_S3_pos;
int C_S0_pos, C_S1_pos, C_S2_pos, C_S3_pos;
int POT_0, POT_1, POT_2, POT_3;
int JOY_X1, JOY_Y1, JOY_X2, JOY_Y2;

int recordButtonPin = 5;
int playButtonPin = 6;
int resetButtonPin = 9;
int optionalButtonPin = 11;
int recordButtonState = 0;
int playButtonState = 0;
int resetButtonPush = 0;
int optionalButtonPush = 0;

int saved_data[500];
int array_index = 0;
char incoming = 0;
int action_pos;
int action_servo;

int potentiometerPin0 = A0;
int potentiometerPin1 = A1;
int potentiometerPin2 = A2;
int potentiometerPin3 = A3;
int joystickPinX1 = A12;
int joystickPinY1 = A13;
int joystickPinX2 = A10;
int joystickPinY2 = A11;

void setup() {
  Serial.begin(9600);
  pinMode(recordButtonPin, INPUT);
  pinMode(playButtonPin, INPUT);
  pinMode(resetButtonPin, INPUT);
  pinMode(optionalButtonPin, INPUT);
  // Attach an interrupt to the reset button pin
  Servo_0.attach(23, 0, 70);
  Servo_1.attach(33, 0, 90);
  Servo_2.attach(45, 0, 180);
  Servo_3.attach(51, 0, 180);

  Servo_0.write(90);
  Servo_1.write(90);
  Servo_2.write(90);
  Servo_3.write(90);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("MODE MAN or REC!!");
  lcd.setCursor(0,1);
  lcd.print("SWITCH's OPTION:");
  lcd.setCursor(0,2);
  lcd.print("TURN LEFT: MAN");
  lcd.setCursor(0,3);
  lcd.print("TURN RIGHT: REC");
}

void Read_POT() {
  POT_0 = analogRead(potentiometerPin0);
  POT_1 = analogRead(potentiometerPin1);
  POT_2 = analogRead(potentiometerPin2);
  POT_3 = analogRead(potentiometerPin3);
  
  S0_pos = map(POT_0, 0, 1023, 0, 70);
  S1_pos = map(POT_1, 0, 1023, 0, 90);
  S2_pos = map(POT_2, 0, 1023, 0, 180);
  S3_pos = map(POT_3, 0, 1023, 0, 180);
}

void Read_JOY(){
  JOY_X1 = analogRead(joystickPinX1);
  JOY_Y1 = analogRead(joystickPinY1);
  JOY_X2 = analogRead(joystickPinX2);
  JOY_Y2 = analogRead(joystickPinY2);
  
  S4_pos = map(JOY_X1, 0, 1023, 0, 70);
  S5_pos = map(JOY_Y1, 0, 1023, 0, 90);
  S6_pos = map(JOY_X2, 0, 1023, 0, 180);
  S7_pos = map(JOY_Y2, 0, 1023, 0, 180);
}
void Record() {
  Read_POT();
  P_S0_pos = S0_pos;
  P_S1_pos = S1_pos;
  P_S2_pos = S2_pos;
  P_S3_pos = S3_pos;
  Read_POT();
  if (P_S0_pos == S0_pos) {
    Servo_0.write(S0_pos);
    if (C_S0_pos != S0_pos) {
      saved_data[array_index] = S0_pos + 0;
      array_index++;
    }
    C_S0_pos = S0_pos;
  }
  if (P_S1_pos == S1_pos) {
    Servo_1.write(S1_pos);
    if (C_S1_pos != S1_pos) {
      saved_data[array_index] = S1_pos + 1000;
      array_index++;
    }
    C_S1_pos = S1_pos;
  }
  if (P_S2_pos == S2_pos) {
    Servo_2.write(S2_pos);
    if (C_S2_pos != S2_pos) {
      saved_data[array_index] = S2_pos + 2000;
      array_index++;
    }
    C_S2_pos = S2_pos;
  }
  if (P_S3_pos == S3_pos) {
    Servo_3.write(S3_pos);
    if (C_S3_pos != S3_pos) {
      saved_data[array_index] = S3_pos + 3000;
      array_index++;
    }
    C_S3_pos = S3_pos;
  }
  /*
  lcd.setCursor(0, 1);
  lcd.print("1: ");
  lcd.print(S0_pos);
  lcd.setCursor(8, 1);
  lcd.print("2: ");
  lcd.print(S1_pos);
  lcd.setCursor(0, 2);
  lcd.print("3: ");
  lcd.print(S2_pos);
  lcd.setCursor(8, 2);
  lcd.print("4: ");
  lcd.print(S3_pos);
  delay(100);*/
}

void Play() {
  for (int Play_action = 0; Play_action < array_index; Play_action++) {
    action_servo = saved_data[Play_action] / 1000;
    action_pos = saved_data[Play_action] % 1000;
    switch (action_servo) {
      case 0:
        Servo_0.write(action_pos);
        break;
      case 1:
        Servo_1.write(action_pos);
        break;
      case 2:
        Servo_2.write(action_pos);
        break;
      case 3:
        Servo_3.write(action_pos);
        break;
    }
    delay(500);
  }
}
void loop() {
  recordButtonState = digitalRead(recordButtonPin);
  playButtonState = digitalRead(playButtonPin);
  resetButtonPush = digitalRead(resetButtonPin);
  optionalButtonPush = digitalRead(optionalButtonPin);
  if (recordButtonState == HIGH) {
    while (recordButtonState == HIGH) {
      recordButtonState = digitalRead(recordButtonPin);
    }
    Record();
  }
  else if (playButtonState == HIGH) {
    while (playButtonState == HIGH) {
      playButtonState = digitalRead(playButtonPin);
    }
    Play();
  }
  // Joystick Control
  Read_JOY();
  Servo_0.write(S4_pos);
  Servo_1.write(S5_pos);
  Servo_2.write(S6_pos);
  Servo_3.write(S7_pos);
  // Display joystick values on LCD
  /*lcd.setCursor(0, 0);
  lcd.print("MANUAL MODE");
  lcd.setCursor(0, 1);
  lcd.print("X1: ");
  lcd.print(JOY_X1);
  lcd.setCursor(8, 1);
  lcd.print("Y1: ");
  lcd.print(JOY_Y1);
  lcd.setCursor(0, 2);
  lcd.print("X2: ");
  lcd.print(JOY_X2);
  lcd.setCursor(8, 2);
  lcd.print("Y2: ");
  lcd.print(JOY_Y2);
  delay(100);*/
  
}