const int NUMBER_OF_KNOBS = 5;
const int analogInputs[NUMBER_OF_KNOBS] = {A0,A1,A2,A3,A4};

int analogKnobValues[NUMBER_OF_KNOBS];

void setup() {
  // put your setup code here, to run once:
  for(int i = 0; i < NUMBER_OF_KNOBS; i++){
    pinMode(analogInputs[i],INPUT);
  }
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
    updateSliderValues();
    sendSliderValues();
    delay(10);
    //printSliderValues();
}

void updateSliderValues(){
  for(int i = 0; i < NUMBER_OF_KNOBS; i++){
    analogKnobValues[i] = analogRead(analogInputs[i]);
  }
}

void sendSliderValues(){
  String builtString = String("");

  for(int i = 0; i < NUMBER_OF_KNOBS; i++){
    builtString += String((int)map(analogKnobValues[i], 0, 1023, 0, 100));

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

