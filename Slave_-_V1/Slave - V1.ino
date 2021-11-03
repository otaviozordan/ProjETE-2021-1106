#include <Stepper.h>
#include <EEPROM.h>

int address; //Endereço de salvamento da EEPROM

const int stepsPerRevolution = 200;  // Define o numero de passo por volta (de acordo com seu motor) 

Stepper myStepper(stepsPerRevolution, 6, 7, 8, 9); //Declara motor nos pinos 6 à 9

String recive;
float gama, gamaAnterior;

void setup() {
  myStepper.setSpeed(60); //Define a velocidade de rotação do motor para 60 rpm
  
  Serial.begin(9600); //Inicia comunicação serial
  
  pinMode(10, INPUT);

  gamaAnterior = EEPROM.read(address); //Le valor salvo na EEPROM
}

void loop() {

  if (Serial.available() && digitalRead(10) == 1){
    gama = Serial.read();

    if (gama != gamaAnterior){
      myStepper.step((gama-gamaAnterior)*360);

      Serial.println("Corrigindo");   
      Serial.println(gama-gamaAnterior);

      gamaAnterior = gama;

      EEPROM.update(address, gamaAnterior); //Atualiza o valor na EEPROM
    }
    
  }

 
  delay(1);

  
}