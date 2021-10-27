#include <Stepper.h>

const int stepsPerRevolution = 200;  // Define o numero de passo por volta (de acordo com seu motor) 

Stepper myStepper(stepsPerRevolution, 6, 7, 8, 9); //Declara motor nos pinos 6 à 9

String recive;
float gama;

void setup() {
  myStepper.setSpeed(60); //Define a velocidade de rotação do motor para 60 rpm
  
  Serial.begin(9600); //Inicia comunicação serial
  
  pinMode(10, INPUT);

}

void loop() {

  if (Serial.available() && digitalRead(10) == 1){
    recive = Serial.readString(); 
    Serial.println("Corriindo");   
    myStepper.step(gama*360);
  }

 
  delay(1);

  
}
