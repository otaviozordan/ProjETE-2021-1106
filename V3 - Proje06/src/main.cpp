//Projeto: V3 - Projete
//Autor Inicial: Otávio Zordan
//Colaboradores: 

// Debug :
// SetHigh - Para fazer a leitura de carga vazia 

#include <Arduino.h>
#include <LiquidCrystal.h> // Adiciona a biblioteca "LiquidCrystal" ao projeto
#include <SoftwareSerial.h> //Para comunicação entre arduinos

SoftwareSerial slaveBoard (2, 3); //Informa a conexão com slave
LiquidCrystal lcd(12, 13, 7, 6, 5, 4); // Pinagem do LCD

String recive;

long hif, hit;
long hmf, hmt;
long diff, dift, dif;
float lh;

// Para leitura: *********************************
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
  //Serial.println(distanceT);
  delay(50);

}

void leituraF(){ //Leitura frontal

  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn (echoPin2, HIGH);

  distanceF = duration2/97.7;
  //Serial.println(distanceF);
  delay(50);

}

//****************************************************


void setup()
{
  pinMode(trigPin1, OUTPUT); //Define os pinos do ultrassonico 1
  pinMode(echoPin1, INPUT);

  pinMode(trigPin2, OUTPUT); //Define os pinos do ultrassonico 2
  pinMode(echoPin2, INPUT);

  Serial.begin(9600); //Inicia monito serial
  lcd.begin(16, 2); // Inicia o lcd de 16x2

}

void loop() {

  if(Serial.available()){  //Verifica a chegada de algo pela serial
    recive = Serial.readString(); //Realiza a importação de comandos de debug pelo serial
    //Serial.println(recive);
  }
    
  if(recive == "SetHigh"){ //Para fazer a leitura - SetHigh 
    Serial.println("Iniciando SetHigh");
    lcd.setCursor(0,5);
    lcd.print("Start");
    lcd.setCursor(1,4);
    lcd.print("SetHigh");

    leituraT();
    leituraF();
    hif = distanceF;
    hit = distanceT;

    lcd.setCursor(0,0);
    lcd.print(hif);
    lcd.setCursor(1,0);
    lcd.print(hit);

    Serial.println("As distancias definidas como padrao foram: ");
    Serial.print(hif);
    Serial.println(" para F");
    Serial.print(hit);
    Serial.println(" para T");

    delay(200);
    recive = "";
  }
 
  if (recive == "Lhigh") {

    if(Serial.available()){  //Verifica a chegada de algo pela serial
     lh = Serial.read(); //Realiza a importação de comandos de debug pelo serial
      Serial.println("Recebemos o valor de:");
      Serial.println(lh);
    }
    recive = "";
  }
  
  if(recive == "Calibrate"){ 
    Serial.println("Iniciando Calibrate");
    lcd.setCursor(0,5);
    lcd.print("Start");
    lcd.setCursor(1,3);
    lcd.print("Calibrate");

    leituraT();
    leituraF();
    hmf = distanceF;
    hmt = distanceT;

    diff = hif-hmf;
    dift = hit-hmt;
    dif = diff-dift;

    recive = "";
  }


}
