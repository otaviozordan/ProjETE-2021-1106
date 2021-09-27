//Projeto: V3 - Projete
//Autor: Otávio Zordan

/*Debug :
SetHigh - Para fazer a leitura de carga vazia */


#include <Arduino.h>
#include <LiquidCrystal.h> // Adiciona a biblioteca "LiquidCrystal" ao projeto

LiquidCrystal lcd(12, 13, 7, 6, 5, 4); // Pinagem do LCD

String recive;


//******* Leitura *********************************
//Para leitura:
const int echoPin1 = 9;
const int trigPin1 = 10;

const int echoPin2 = 11;
const int trigPin2 = 12;

long duration1 ,distanceT;
long duration2 ,distanceF;


void leituraT(){ //Leitura traseira

  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn (echoPin1, HIGH);

  distanceT = duration1/97.7;
  Serial.println(distanceT);
  delay(50);

  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn (echoPin1, HIGH);

  distanceT = duration1/58.2;
  Serial.println(distanceT);
  delay(50);

}

void leituraF(){ //Leitura frontal

  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn (echoPin2, HIGH);

  distanceF = duration1/97.7;
  Serial.println(distanceF);
  delay(50);

  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn (echoPin2, HIGH);

  distanceF = duration1/58.2;
  Serial.println(distanceF);
  delay(50);

}

//****************************************************


void setup()
{
  Serial.begin(9600); //Inicia monito serial
  lcd.begin(16, 2); // Inicia o lcd de 16x2


}

void loop() {

  if(Serial.available()){ //Realiza a importação de comandos de debug pelo serial
    recive = Serial.readString();
  }
    
  if(recive == "SetHigh"){ //Para fazer a leitura - SetHigh 
    leituraT();
    leituraF();
  }


  Serial.println(recive);
  Serial.println(distanceF);
  Serial.println(distanceT);
}
