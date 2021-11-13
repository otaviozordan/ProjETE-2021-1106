#include <EEPROM.h>
#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int address; //Endereço de salvamento da EEPROM

String recive;
float gama, gamaAnterior;

void setup() {
  Serial.begin(9600); //Inicia comunicação serial
  
  pinMode(10, INPUT);

  gamaAnterior = EEPROM.read(address); //Le valor salvo na EEPROM

  myservo.attach(9);  // attaches the servo on pin 9 to the servo 

  myservo.write(0);
  delay(500);
  myservo.write(gamaAnterior); 
}

void loop() {

  if (Serial.available() && digitalRead(10) == 1){
    gama = Serial.read();

    if (gama != gamaAnterior){
      while(gama > 180){
          myservo.write(180); 
          gama = gama-180;
          delay(50);
          
          myservo.write(0);
          delay(1000);
        }
        
        if (gama < 180){
          myservo.write(gama);
        }

      Serial.println("Corrigindo");   
      Serial.println(gama-gamaAnterior);

      gamaAnterior = gama;

      EEPROM.update(address, gamaAnterior); //Atualiza o valor na EEPROM
    }
    
  }

 
  delay(1);

  
}
