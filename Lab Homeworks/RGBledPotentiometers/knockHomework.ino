int speakerPin = A0;
int buzzerPin = 11;
int buttonPin = 2;

int buttonState = 0;
int buzzerTone = 1000;
int speakerValue = 0;
const int threshold = 10;
unsigned long previousMillis = 0;
const long interval = 5000;

void setup() {
  pinMode(speakerPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);

}

void loop() {
  if(speakerValue < threshold){
    speakerValue = analogRead(speakerPin);
    previousMillis = millis();
  }
  
  if(speakerValue != 0)
    Serial.println(speakerValue);
    
  if(speakerValue >= threshold){
      Serial.println("Knock");
      if(millis() - previousMillis >= interval)
          tone(buzzerPin, buzzerTone);
          buttonState = digitalRead(buttonPin);
           //Serial.println(buttonState);
           if(buttonState != 0){
                noTone(buzzerPin);
                speakerValue = 0;
              }      
      }
}
