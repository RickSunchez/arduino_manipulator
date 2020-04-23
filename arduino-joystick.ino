#include <Servo.h>

#define pinX2   A1  // ось X джойстика
#define pinY2   A2  // ось Y джойстика
#define pinX1   A4  // ось Y джойстика
#define pinY1   A5  // ось Y джойстика
#define swPin1  7  // кнопка джойстика
#define swPin2  8  // кнопка джойстика

#define servo1  10  // светодиод на Pin 13
#define servo2  11  // светодиод на Pin 13
#define servo3  12  // светодиод на Pin 13

int amplitude = 10;

Servo Servo1;
Servo Servo2;
Servo Servo3;

int servo1_angle = 0;
int servo2_angle = 0;
int servo3_angle = 0;
bool servo2_on = false;

void setup() {
  Serial.begin(9600);
  
  pinMode(pinX1, INPUT);
  pinMode(pinY1, INPUT);
  pinMode(pinX2, INPUT);
  pinMode(pinY2, INPUT);
  
  pinMode(swPin1, INPUT);
  pinMode(swPin2, INPUT);
  digitalWrite(swPin1, HIGH);

  Servo1.attach(servo1);
  Servo2.attach(servo2);
  Servo3.attach(servo3);

  Servo1.write(0);
  Servo2.write(0);
  Servo3.write(0);

  Serial.println("Calibrate start");
  int count = 0;
  int X[] = {2000, 0};
  int Y[] = {2000, 0};
  
  while (count < 1000) {
    int x = analogRead(pinX1);
    int y = analogRead(pinY1);
    
    if (x < X[0]) X[0] = x;
    if (x > X[1]) X[1] = x;

    if (y < Y[0]) Y[0] = y;
    if (y > Y[1]) Y[1] = y;

    if (count % 10 == 0) Serial.print(".");
    count++;
  }
  Serial.println("\nCalibrate end");
  Serial.print("minX = "    + String( X[0]));
  Serial.println(" maxX = " + String( X[1]));
  Serial.print("minY = "    + String( Y[0]));
  Serial.println(" maxY = " + String( Y[1]));
}
 
void loop() {
  int X1 = analogRead(pinX1);              // считываем значение оси Х
  int Y1 = analogRead(pinY1);              // считываем значение оси Y

  boolean currentState = digitalRead(swPin1);

  if (!currentState) {
    if (servo2_on) {
      servo2_on = false;
    }
    else {
      servo2_on = true;
    }
  }
  delay(100);
  
  if (!servo2_on) {
    if (X1 > 800) servo1_angle-=5;
    if (X1 < 300) servo1_angle+=5;
    
    if (servo1_angle > 85) servo1_angle = 85;
    if (servo1_angle < 0) servo1_angle = 0;
    Servo1.write(servo1_angle);
    Serial.println(servo1_angle);
  }
  else {
    if (X1 > 800) servo2_angle-=5;
    if (X1 < 300) servo2_angle+=5;
    
    if (servo2_angle > 85) servo2_angle = 85;
    if (servo2_angle < 0) servo2_angle = 0;
    Servo2.write(servo2_angle);
  }
  
  int X2 = analogRead(pinX2);              // считываем значение оси Х
  int Y2 = analogRead(pinY2);              // считываем значение оси Y

  if (X2 > 800) servo3_angle-=5;
  if (X2 < 300) servo3_angle+=5;

  if (servo3_angle > 180) servo3_angle = 180;
  if (servo3_angle < 0)  servo3_angle = 0;
  Servo3.write(servo3_angle);
  
  delay(25);
}
