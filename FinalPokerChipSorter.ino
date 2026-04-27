#include <Wire.h>
#include "Adafruit_TCS34725.h"
 
// ---------------- MOTOR ----------------
#define PWMA 5
#define AIN1 7
#define AIN2 8
 
// ---------------- SENSOR ----------------
Adafruit_TCS34725 tcs = Adafruit_TCS34725(
  TCS34725_INTEGRATIONTIME_50MS,
  TCS34725_GAIN_4X
);
 
// ---------------- SETUP ----------------
void setup() {
  Serial.begin(9600);
 
  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
 
  if (!tcs.begin()) {
    Serial.println("Sensor not found");
    while (1);
  }
 
  Serial.println("Sensor ready");
}
 
// ---------------- LOOP ----------------
void loop() {
  uint16_t r, g, b, c;
 
  tcs.getRawData(&r, &g, &b, &c);
 
  String color = classifyColor(r, g, b);
 
  Serial.print("Detected: ");
  Serial.println(color);
 
  actOnColor(color);
 
  delay(2000);
}
 
// ---------------- COLOR CLASSIFICATION ----------------
String classifyColor(uint16_t r, uint16_t g, uint16_t b) {
  //Serial.println("%d %d %d", r, g, b);
  //Serial.println(r, g, b);'
  //Serial.printf("%d %d %d\n", r, g, b);
  Serial.print(r);
Serial.print(" ");
Serial.print(g);
Serial.print(" ");
Serial.println(b);
  /*if (r > 250 && g > 250 && b > 250)
    return "WHITE";
 
  if (r < 150 && g < 150 && b < 100)
    return "BLUE";
 
  if (r > g && r > b && r >= 175)
    return "RED";
 
  if (g > r && g > b && g > 95)
    return "GREEN";
 
  if (b > r && b > g)
    return "BLUE";
 
  return "UNKNOWN";*/
 
  //DARKNESS CODE:
  if (r > 250 && g > 250 && b > 250)
    return "WHITE";
 
  if (r > g && r > b && r >= 500)
    return "RED";
 
  if (g > r && g > b && g >= 90)
    return "GREEN";
 
  if (120 < r && 180 > r && g > 120 && g < 180 && b > 120 && b < 180)
    return "BLUE";
 
  if (r < 160 && g < 120 && b < 90 && r > 50 && g > 50 && b > 50)
    return "BLACK";
 
  return "UNKNOWN";
}
 
// ---------------- MOTOR ACTION ----------------
void actOnColor(String color) {
 
  if (color == "RED") {
    Serial.println("Rotating for Red");
    rotateCW(200);
    delay(500);
    rotateCCW(200);
  }
  else if (color == "BLUE") {
    Serial.println("Rotating for Blue");
    rotateCCW(425);
    delay(500);
    rotateCW(425);
  }
  else if (color == "GREEN") {
    Serial.println("Rotating for Green");
    rotateCCW(200);
    delay(500);
    rotateCW(200);
  }
  else if (color == "WHITE") {
    Serial.println("Rotating for White");
    //rotateCCW(100);
  }
  else if (color == "BLACK") {
    Serial.println("Stopping for Black");
    //stopMotor();
  }
}
 
// ---------------- MOTOR FUNCTIONS ----------------
void rotateCW(int duration) {
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  analogWrite(PWMA, 180);
  delay(duration);
  stopMotor();
}
 
void rotateCCW(int duration) {
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  analogWrite(PWMA, 180);
  delay(duration);
  stopMotor();
}
 
void stopMotor() {
  analogWrite(PWMA, 0);
}
 
 