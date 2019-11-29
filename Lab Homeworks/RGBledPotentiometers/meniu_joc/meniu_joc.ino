#include <LiquidCrystal.h>
const int RS = 12;
const int enable = 11;
const int d4 = 5;
const int d5 = 4;
const int d6 = 3;
const int d7 = 2;
LiquidCrystal lcd(RS, enable, d4, d5, d6, d7);

const int pinSW = 13; // digital pin connected to switch output
const int pinX = A0; // A0 - analog pin connected to X output
const int pinY = A1; // A1 - analog pin connected to Y output

bool joyMoved = false;
//int digit = 0;
int minThreshold = 400;
int maxThreshold = 600;
int curssor;
int col = 0;
int ok = 0;
int row = 0;
int prev = 0;
const int interval = 5000;
int switchValue;
int buttonState = 0;
int cursorValue = 0;
int xValue = 0;
int yValue = 0;
int i = 0;
int setupStartingLevel = 0;
int startingLevelValue = 0;
void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(pinSW, INPUT_PULLUP);
  pinMode(pinX, INPUT);
  lcd.setCursor(1, 0);
  lcd.print("Start");
  lcd.setCursor(8, 0);
  lcd.print("Setup");
  lcd.setCursor(1, 1);
  lcd.print("HighScore");
  //currsor = lcd.setCursor(0,0);
}
bool buttonPressed(int buttonValue) {
  if (buttonValue == LOW) {
    return true;
  }
  return false;
}
void optionsStart(int startingLevelValue) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Lives:3");
  lcd.setCursor(8, 0);
  lcd.print("Level:");
  lcd.setCursor(14, 0);
  lcd.print(startingLevelValue);
  lcd.setCursor(0, 1);
  lcd.print("Score:");
  lcd.setCursor(6, 1);
  lcd.print(startingLevelValue * 3);
}
void loop() {

  if (buttonState == LOW) {
    int buttonValue = digitalRead(pinSW);
    if (buttonPressed(buttonValue) == true) {
      buttonState = !buttonState;
    }
    xValue = analogRead(pinX);
    if (xValue > maxThreshold && joyMoved == false) {
      cursorValue++;
      if (cursorValue == 3) {
        cursorValue = 0;
      }
      joyMoved = true;
    }
    if (xValue < minThreshold && joyMoved == false) {
      cursorValue--;
      if (cursorValue == -1) {
        cursorValue = 2;
      }
      joyMoved = true;
    }
    if (xValue < maxThreshold && xValue > minThreshold) {
      joyMoved = false;
    }
    lcd.setCursor(0, 0);
    if (cursorValue == 0) {
      lcd.print(">Start");
    } else {
      lcd.print(" Start");
    }
    lcd.setCursor(7, 0);
    if (cursorValue == 1) {
      lcd.print(">Setup");
    } else {
      lcd.print(" Setup");
    }
    lcd.setCursor(0, 1);
    if (cursorValue == 2) {
      lcd.print(">HighScore");
    } else {
      lcd.print(" HighScore");
    }
  } else {
    if (cursorValue == 0) {
      int current = millis();
      if ((current - prev) > interval && i < 2) {
        optionsStart(startingLevelValue);
        startingLevelValue++;
        i++;
        prev = current;
      }
      if (i == 2) {
        if (buttonState == HIGH) {
          if(ok == 0) {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("congrats");
            lcd.setCursor(0, 1);
            lcd.print("exit");
            ok = 1;
          }
          int buttonValue = digitalRead(pinSW);
          if (buttonPressed(buttonValue) == true) {
            buttonState = !buttonState;
            ok = 0;
            i = 0;
          }
        }
      }
    }
    if (cursorValue == 1) {
      if (ok == 0) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Starting Level:");
        ok = 1;
      }
      yValue = analogRead(pinY);
      if (yValue > maxThreshold && joyMoved == false) {
        startingLevelValue++;
        joyMoved = true;
      }
      if (yValue < minThreshold && joyMoved == false) {
        startingLevelValue--;
        joyMoved = true;
      }
      if (yValue < maxThreshold && yValue > minThreshold) {
        joyMoved = false;
      }
      lcd.setCursor(0, 1);
      lcd.print(startingLevelValue);
      if (buttonState == HIGH) {
        int buttonValue = digitalRead(pinSW);
        if (buttonPressed(buttonValue) == true) {
          buttonState = !buttonState;
          ok = 0;
        }
      }

    }
    if (cursorValue == 2) {
      if (ok == 0) {
        lcd.clear();
        ok = 1;
      }
      lcd.setCursor(0, 0);
      lcd.print("HighScore is:");
      lcd.setCursor(0, 1);
      lcd.print(startingLevelValue * 3);
      if (buttonState == HIGH) {
        int buttonValue = digitalRead(pinSW);
        if (buttonPressed(buttonValue) == true) {
          buttonState = !buttonState;
          ok = 0;
        }
      }
    }

  }
}
