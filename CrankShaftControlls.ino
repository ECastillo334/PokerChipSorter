#define PWMA 5
#define AIN1 7
#define AIN2 8
#define BUTTON 4
 
bool running = false;
 
void setup() {
  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
}
 
void loop() {
  // Button press
  if (digitalRead(BUTTON) == LOW && !running) {
    delay(50); // debounce
    if (digitalRead(BUTTON) == LOW) {
      running = true;
 
      // Run motor
      Serial.println("Running motor");
      digitalWrite(AIN1, HIGH);
      digitalWrite(AIN2, LOW);
      analogWrite(PWMA, 150);
 
      delay(500); // this controls rotation amount (tune this)
 
      Serial.println("Stopping motor");
      stopMotor();
      running = false;
    }
  }
}
 
void stopMotor() {
  analogWrite(PWMA, 0);
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW);
}
 