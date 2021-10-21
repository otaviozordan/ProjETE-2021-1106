#include <Stepper.h>

const int stepsPerRevolution = 200;  // Define o numero de passo por volta (de acordo com seu motor) 

Stepper myStepper(stepsPerRevolution, 6, 7, 8, 9); //Declara motor nos pinos 6 à 9

String recive;
long dift, diff, dif, k;


void setup() {
  myStepper.setSpeed(60); //Define a velocidade de rotação do motor para 60 rpm
  
  Serial.begin(9600); //Inicia comunicação serial
  
  pinMode(5, OUTPUT);
  digitalWrite(5, HIGH);
  k = 0;
}

void loop() {

  if (Serial.available()){
    recive = Serial.read();    
  }

  if (recive == "Diferenca traseira de: ") {
    Serial.println("Diferenca traseira recebida: ");    
    while(!Serial.available()){}  
  
    if(Serial.available()){
       dift == Serial.read();
    }
  } 

  if (recive == "Diferenca frontal de: ") {
    Serial.println("Diferenca recebida");    
    while(!Serial.available()){}  
  
    if(Serial.available()){
       diff == Serial.read();
    }
  } 

  if (recive == "Diferenca entre eixos de: ") {
    Serial.println("Diferenca entre eixos receida");    
    while(!Serial.available()){}  
  
    if(Serial.available()){
       dif == Serial.read();
    }
  } 
  delay(1);
  myStepper.step(k+1);
  
}
