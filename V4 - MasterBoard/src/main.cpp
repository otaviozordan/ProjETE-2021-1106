//Projeto: V4 - Projete
//Autor Inicial: Otávio Zordan, Rayssa Paduan, Kayque Amado, Beatriz Lacerda, Leticia Rodrigues

#include <Arduino.h>
#include <LiquidCrystal.h> //Adiciona a biblioteca "LiquidCrystal" ao projeto

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // Pinagem do LCD

String recive;

float hif, hit;
float hmf, hmt;
float diff, dift, dif;
float lh;

// Para leitura: *********************************
const int echoPin1 = 7;
const int trigPin1 = 6;

const int echoPin2 = 9;
const int trigPin2 = 8;

float duration1 ,distanceT;
float duration2 ,distanceF;

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


void setup(){
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
    Serial.println("Comando recebido");
  }
    
  if(recive == "SetHigh"){ //Para fazer a leitura - SetHigh 
    Serial.println("Iniciando SetHigh");

    lcd.setCursor(5,0);
    lcd.print("Start");
    lcd.setCursor(4,1);
    lcd.print("SetHigh");
    delay(400);

    leituraT();
    leituraF();
    hif = distanceF;
    hit = distanceT;

    lcd.setCursor(0,0);
    lcd.print("H set traseiro");
    lcd.setCursor(0,1);
    lcd.print(hit);
    delay(500);
    lcd.clear();

    lcd.setCursor(0,0);
    lcd.print("H set frontal");
    lcd.setCursor(0,1);
    lcd.print(hif);
    delay(500);
    lcd.clear();

    Serial.println("As distancias definidas como padrao foram: ");
    Serial.print(hif);
    Serial.println(" para F");
    Serial.print(hit);
    Serial.println(" para T");

    recive = "";
  }
 
  if (recive == "LHigh") {
    if(Serial.available()){  //Verifica a chegada de algo pela serial
      lh = Serial.read();

      lcd.setCursor(5,0);
      lcd.print("LHigh");
      lcd.setCursor(4,1);
      lcd.print(lh);

      Serial.println("Recebemos o valor de:");
      Serial.println(lh);
      recive = "";
    }
  }
  
  if(recive == "Calibrate"){ 
    Serial.println("Iniciando Calibrate");

    lcd.setCursor(5,0);
    lcd.print("Start");
    lcd.setCursor(3,1);
    lcd.print("Calibrate");
    delay(500);
    lcd.clear();

    leituraT();
    leituraF();
    hmf = distanceF;
    hmt = distanceT;

    diff = hif-hmf;
    dift = hit-hmt;
    dif = diff-dift;

    lcd.setCursor(0,0);
    lcd.print("Comprecao t de");
    lcd.setCursor(0,1);
    lcd.print(dift);
    delay(500);
    lcd.clear();

    lcd.setCursor(0,0);
    lcd.print("Comprecao f de");
    lcd.setCursor(0,1);
    lcd.print(diff);
    delay(500);
    lcd.clear();

    lcd.setCursor(0,0);
    lcd.print("Diferenca de: ");
    lcd.setCursor(0,1);
    lcd.print(dif);
    delay(500);
    lcd.clear();

    Serial.print("Diferenca traseira de: ");
    Serial.println(dift);

    Serial.print("Diferenca frontal de: ");
    Serial.println(diff);   

    Serial.print("Diferenca entre eixos de: ");
    Serial.println(dif);

    lcd.setCursor(3, 0);
    lcd.print("Calibrado");
    delay(400);
    lcd.clear();
    recive = "";
    delay(500);
  }
  
    if(recive == "Zerar"){ 
      Serial.println("Zerando Valores");
      hif = 0;
      hit = 0;
    }

}