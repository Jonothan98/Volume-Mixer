#include <ezButton.h>

const int NUMBER_OF_KNOBS = 5;
const int analogInputs[NUMBER_OF_KNOBS] = {A0,A1,A2,A3,A4};
const int digitalPins[4] = {2,3,4,5};

const int muteKeyPin = 2; 
const int muteLedPin = 3;
const int pauseKeyPin = 4;
const int pauseLedPin = 5;

ezButton muteButton(muteKeyPin);
ezButton pauseButton(pauseKeyPin);

int muteKeyState = 0;
int pauseKeyState = 0;
int micVolumeLevel = 1023;
bool muteAll = false;
int analogKnobValues[NUMBER_OF_KNOBS];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  for(int i = 0; i < NUMBER_OF_KNOBS; i++){
    pinMode(analogInputs[i],INPUT);
  }

  pinMode(muteLedPin,OUTPUT);
  pinMode(muteKeyPin,INPUT_PULLUP);

  pinMode(pauseLedPin,OUTPUT);
  pinMode(pauseKeyPin, INPUT_PULLUP);

  muteButton.setDebounceTime(100);
   
}

void loop() {
  // put your main code here, to run repeatedly:
    updateSliderValues();
    sendSliderValues();
    delay(10);

    muteKeyState = digitalRead(muteKeyPin);
    pauseKeyState = digitalRead(pauseKeyPin);
    muteButton.loop();
    pauseButton.loop();

    if(muteButton.isPressed()){
      toggleLed(muteLedPin);
    }

    if(pauseButton.isPressed()){
      toggleLed(pauseLedPin);
    }

}

void toggleLed(int ledPin){
  if(digitalRead(ledPin) == LOW){
    digitalWrite(ledPin,HIGH);
    if(ledPin == 3){
      micVolumeLevel = 0;
    } else {
      muteAll = true;
    }
  } else {
    digitalWrite(ledPin,LOW);
    if(ledPin == 3){
      micVolumeLevel = 1023;
    } else {
      muteAll = false;
    }
  }
}

void updateSliderValues(){
  for(int i = 0; i < NUMBER_OF_KNOBS-1; i++){
    analogKnobValues[i] = analogRead(analogInputs[i]);
  }
}

void sendSliderValues(){
  String builtString = String("");

  for(int i = 0; i < NUMBER_OF_KNOBS; i++){
    if(i == 4){
      builtString += String(micVolumeLevel);
    } else if(muteAll == true) {
      builtString += String((int) 0);
    } else {
      builtString += String((int)analogKnobValues[i]);
    }

    if(i < NUMBER_OF_KNOBS -1){
      builtString += String("|");
    }
  }

  Serial.println(builtString);

}

void printSliderValues(){
  for(int i = 0; i < NUMBER_OF_KNOBS; i++){
    String printedString = String("Slider #") + String(i+1) + String(": ") + String(analogKnobValues[i]) + String(" mV");
    Serial.write(printedString.c_str());

    if(i< NUMBER_OF_KNOBS - 1){
      Serial.write(" | ");
    } else {
      Serial.write("\n");
    }
  }
}

