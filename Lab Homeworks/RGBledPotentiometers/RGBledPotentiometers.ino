//Requirements:
//Breadboard
//Arduino Uno
//Jumper Wires 
//3 potentiometers
//RGB led
//3 resistors

const int potPin1 = A0, potPin2 = A1, potPin3 = A2;
 const int blueLed = 3, greenLed = 5, redLed = 10;
 int potValue1 = 0, potValue2 = 0, potValue3 = 0;
 int ledValue1 = 0, ledValue2 = 0, ledValue3 = 0;
void setup() {
  pinMode(potPin1, INPUT);
  pinMode(blueLed, OUTPUT);
  pinMode(potPin2, INPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(potPin3, INPUT);
  pinMode(redLed, OUTPUT);

}

void loop() {
  
  potValue1 = analogRead(potPin1);
  ledValue1 = map(potValue1, 0, 1023, 0, 255);
  analogWrite(blueLed, ledValue1);
  potValue2 = analogRead(potPin2);
  ledValue2 = map(potValue2, 0, 1023, 0, 255);
  analogWrite(greenLed, ledValue2);
  potValue3 = analogRead(potPin3);
  ledValue3 = map(potValue3, 0, 1023, 0, 255);
  analogWrite(redLed, ledValue3);
  
}
