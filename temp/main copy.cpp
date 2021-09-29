#include <Arduino.h>
#include <Stepper.h>
#include <SoftwareSerial.h>

SoftwareSerial masterBoard (10, 13);

const int stepsPerRevolution = 360;
Stepper myStepper(stepsPerRevolution, 8,9,10,11);     

void setup(){
  masterBoard.begin(9600);
  myStepper.setSpeed(60);
}

void loop() {


}