//declaring the pins of the 7-segment
const int pinA = 12;
const int pinB = 8;
const int pinC = 5;
const int pinD = 3;
const int pinE = 2;
const int pinF = 11;
const int pinG = 6;
const int pinDP = 4;
const int pinD1 = 7;
const int pinD2 = 9;
const int pinD3 = 10;
const int pinD4 = 13;

//declaring the pins of the joystick
const int pinSW = A2; // digital pin connected to switch output
const int pinX = A0; // A0 - analog pin connected to X output
const int pinY = A1; // A1 - analog pin connected to Y output

const int segSize = 8;
const int noOfDisplays = 4; //4 digits
const int noOfDigits = 10; // 0-9 no.

int dpState = LOW;

int swState = LOW;
int lastSwState = LOW;
int switchValue;
int xValue = 0;
int yValue = 0;
bool joyMoved = false;
bool joyMovedy = false;
int digit = 0;
int minThreshold= 400;
int maxThreshold= 600;
int num = 0;

int currentDisplay = 0;

int swValue = 0;

int segments[segSize] = {
pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP
};

int digits[noOfDisplays] = {
pinD1, pinD2, pinD3, pinD4
};

int screen[noOfDigits] = {
  0, 0, 0, 0
};

byte digitMatrix[noOfDigits][segSize - 1] = {
// a b c d e f g
{1, 1, 1, 1, 1, 1, 0}, // 0
{0, 1, 1, 0, 0, 0, 0}, // 1
{1, 1, 0, 1, 1, 0, 1}, // 2
{1, 1, 1, 1, 0, 0, 1}, // 3
{0, 1, 1, 0, 0, 1, 1}, // 4
{1, 0, 1, 1, 0, 1, 1}, // 5
{1, 0, 1, 1, 1, 1, 1}, // 6
{1, 1, 1, 0, 0, 0, 0}, // 7
{1, 1, 1, 1, 1, 1, 1}, // 8
{1, 1, 1, 1, 0, 1, 1} // 9
};

void displayNumber(byte digit, byte decimalPoint) {
  for (int i = 0; i < segSize - 1; i++) {
    digitalWrite(segments[i], digitMatrix[digit][i]);
}
  // write the decimalPoint to DP pin
  digitalWrite(segments[segSize - 1], decimalPoint);
}

void showDigit(int num) {
  for (int i = 0; i < noOfDisplays; i++) {
    digitalWrite(digits[i], HIGH);
}
  digitalWrite(digits[num], LOW);
}


void setup() {
  for (int i = 0; i < segSize - 1; i++)
     pinMode(segments[i], OUTPUT);
  for (int i = 0; i < noOfDisplays; i++)
      pinMode(digits[i], OUTPUT);
  Serial.begin(9600);

}

void loop() {
  xValue = analogRead(pinX);
  yValue = analogRead(pinY);
  swValue = map(swValue, 0, 1023, 0, 255); 
  if(yValue > maxThreshold && joyMovedy == false){
    if(num < 4){
      num++;
    }else{
      num = 0;
    }
    joyMovedy = true;
  }
  if(yValue < minThreshold && joyMovedy == false){
    if(num > 0){
      num--;
    }else{
      num = 4;
    }
    joyMovedy = true;
  }
  if (yValue >= minThreshold && yValue <= maxThreshold) 
    joyMovedy = false;

  
  if (xValue < minThreshold && joyMoved == false) {
    if (digit > 0) {
      digit--;
    } else {
      digit = 9;
    }
    screen[num] = digit;
    joyMoved = true;
    }

  if (xValue > maxThreshold && joyMoved == false) {
    if (digit < 9) {
      digit++;
    } else {
      digit = 0;
    }
    screen[num] = digit;
    joyMoved = true;
    }
  if (xValue >= minThreshold && xValue <= maxThreshold) 
    joyMoved = false;

  
  showDigit(num);
  displayNumber(digit, dpState);
 // for(int i=0; i<noOfDisplays; i++)
 //displayNumber(screen[i], dpState);}
  delay(1);

}
