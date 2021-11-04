//Projeto: V4 - Projete
//Autor Inicial: Otávio Zordan


#include <LiquidCrystal.h> //Adiciona a biblioteca "LiquidCrystal" ao projeto
#include <EEPROM.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // Pinagem do LCD

int address; //Endereço de salvamento da EEPROM

String recive; //String para simular comandos da Central Eletronica

const float clock = 3; //Constante multiplicadora para corrigir o atraso do Tinkercad

float hLeve; //Altura Inicial Fronta, Altura Inicial Traseira
float hcarregado; //Altura Medida Frontal, Altura Medida Traseira


float lh, enex; // Altura Padrão do Faról em ralação ao chão, Entre Eixos 
float teta, alpha, gama; //Anulo de correção

int razaoRegulagem = 360; //Razão do giro do motor pelo modificação do angulo do farol

bool estado; //Para guardar o estado do Slave
int k, comand; //k para mostrar no lcd e comand para executar as configurações

// Para leitura:
const int echoPin1 = 7;
const int trigPin1 = 6;

float duration1 ,distanceT;

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

void setup(){
  pinMode(trigPin1, OUTPUT); //Define os pinos do ultrassonico 1
  pinMode(echoPin1, INPUT);
  
  pinMode(10,INPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  
  Serial.begin(9600); //Inicia monito serial
  lcd.begin(16, 2); // Inicia o lcd de 16x2

  hLeve = 15; 
  lh = 1;
  enex = 3.79;

  EEPROM.update(address, hLeve); //Atualiza o valor na EEPROM
  hLeve = EEPROM.read(address); //Le valor salvo na EEPROM

  digitalWrite(8,HIGH);
}

void loop() {

  k = analogRead(A0);
  k = map(k, 1, 1023, 1, 7);

  if(digitalRead(10) ==1){ //Controle de menu
    comand = k ;
    Serial.println("Selecionado funcao");
    Serial.print(comand);
    Serial.println("");
  }
  
  if(Serial.available()){  //Verifica a chegada de algo pela serial
    recive = Serial.readString(); //Realiza a importação de comandos de debug pelo serial
    Serial.println("Comando recebido");
    Serial.println("");
  }   

  if(recive == "Definir Altura Padrao" || comand == 1){ //Para fazer a leitura - SetHigh 
    Serial.println("Definir altura vazio");

    lcd.setCursor(4,0);
    lcd.print("Definido");
    lcd.setCursor(2,1);
    lcd.print("Altura Vazio");
    delay(2000);
    lcd.clear();

    leituraT();
    hLeve = distanceT;
    EEPROM.update(address, hLeve); //Atualiza o valor na EEPROM

    lcd.setCursor(0,0);
    lcd.print("H padrao traseiro");
    lcd.setCursor(0,1);
    lcd.print(hLeve);
    delay(2000);
    lcd.clear();

    Serial.println("As distancias definidas como padrao foram: ");
    Serial.print(hLeve);
    Serial.println(" para T");
    recive = "";
    Serial.println("");
  }

  else if (recive == "Altura do Farol " || comand == 2) {
    while (!Serial.available){
      lcd.setCursor(3,0);
      lcd.print("Entre com");
      lcd.setCursor(4,1);
      lcd.print("Valores");
      delay(2000);
      lcd.clear()
      Serial.println("Entre com valores:");
      Serial.println("");
    }
    
    if(Serial.available()){  //Verifica a chegada de algo pela serial
      lh = Serial.read();

      lcd.setCursor(5,0);
      lcd.print("H Farol");
      lcd.setCursor(4,1);
      lcd.print(lh);
      delay(2000);
      lcd.clear();

      Serial.println("Recebemos o valor de:");
      Serial.println(lh);
      recive = "";
      Serial.println("");

    }
  }

  else if (recive == "Entre Eixos " || comand == 3) {
    while (!Serial.available)
    {
      lcd.setCursor(3,0);
      lcd.print("Entre com");
      lcd.setCursor(4,1);
      lcd.print("Valores");
      delay(2000);
      lcd.clear();

      Serial.println("Entre com valores:");
      Serial.println("");
    }
    
    if(Serial.available()){  //Verifica a chegada de algo pela serial
      enex = Serial.read();

      lcd.setCursor(3,0);
      lcd.print("Entre Eixo");
      lcd.setCursor(4,1);
      lcd.print(enex);
      delay(2000);
      lcd.clear();

      Serial.println("Recebemos o valor de:");
      Serial.println(enex);
      recive = "";
      Serial.println("");
    }
  }

  else if(recive == "Calibracao" || comand == 4){ 
    Serial.println("Iniciando Calibracao");

    lcd.setCursor(3,0);
    lcd.print("Iniciando");
    lcd.setCursor(2,1);
    lcd.print("Calibracao");
    delay(2000);
    lcd.clear();

    leituraT();
    hcarregado = distanceT;

    alpha = atan(5/lh);

    dif = hLeve-hcarregado;
    teta = atan(dif/enex);

    gama = alpha+teta;

    digitalWrite(9, HIGH);
    delay(5);
    Serial.println(gama);
    delay(5);
    digitalWrite(9, LOW);

    
    lcd.setCursor(0,0);
    lcd.print("Compressao t de");
    lcd.setCursor(0,1);
    lcd.print(dif);
    delay(2000);
    lcd.clear();

    lcd.setCursor(0,0);
    lcd.print("Angulo Gama");
    lcd.setCursor(0,1);
    lcd.print(gama);
    delay(2000);
    lcd.clear();

    lcd.setCursor(1,0);
    lcd.print("Giro no motor");
    lcd.setCursor(0,1);
    lcd.print(gama*razaoRegulagem);
    delay(2000);
    lcd.clear();

    lcd.setCursor(3, 0);
    lcd.print("Calibrado");
    delay(40*clock);
    lcd.clear();
    recive = "";
    Serial.println("");   
  }

  else if(recive == "Zerar" || comand == 5){ 
    Serial.println("Zerando Valores");
    Serial.println(""); 

    EEPROM.update(address, 0); //Atualiza o valor na EEPROM
    hLeve = 0;

    lcd.print("Valores Zerados");
    delay(2000);
    lcd.clear();

    recive = "";
  }

  else if(recive == "Estado do Slave" || comand == 7){  
    lcd.setCursor(0,0);
    lcd.print("ligar/desligar");
    lcd.setCursor(5,1);
    lcd.print("slave");
    delay(2000);
    lcd.clear();    

    if(digitalRead(10) == 1){
      Serial.println("Mudando estado do Slave");
      estado = !estado;
    }

    if(estado == true){
      Serial.println("Ligando Slave");
      Serial.println("");
      digitalWrite(8, HIGH);

      lcd.setCursor(4,0);
      lcd.print("Ligando");
      lcd.setCursor(5,1);
      lcd.print("Slave");
      delay(2000);
      lcd.clear();
    }

    if(estado == false){
      Serial.println("Desligando Slave");
      Serial.println("");
      digitalWrite(8, LOW);

      lcd.setCursor(2,0);
      lcd.print("Desligando");
      lcd.setCursor(5,1);
      lcd.print("Slave");
      delay(2000);
      lcd.clear();      
    }

  }
  
  else{
    switch (k){
      case 1:
        lcd.setCursor(3, 0);
        lcd.print("Definir");
        lcd.setCursor(2, 1);
        lcd.print("Altura Padrao"); 
        delay(20);
        lcd.clear();  
      break;

      case 2:
        lcd.setCursor(1, 0);
        lcd.print("Definir Altura");
        lcd.setCursor(4, 1);
        lcd.print("do Farol"); 
        delay(20);
        lcd.clear();    
      break;

      case 3:
        lcd.setCursor(3, 0);
        lcd.print("Definir");
        lcd.setCursor(2, 1);
        lcd.print("Entre Eixos"); 
        delay(20);
        lcd.clear();     
      break;

      case 4:
        lcd.setCursor(5, 0);
        lcd.print("Fazer");
        lcd.setCursor(3, 1);
        lcd.print("Calibracao");   
        delay(20);
        lcd.clear();
      break;

      case 5:
        lcd.setCursor(3, 0);
        lcd.print("Definir");
        lcd.setCursor(2, 1);
        lcd.print("Valores Zero"); 
        delay(20);
        lcd.clear();  
      break;

      case 6:
        if (k == 6){
          lcd.setCursor(0,0);
          lcd.print("Compressao t de");
          lcd.setCursor(0,1);
          lcd.print(dif);
          delay(200*clock);
          lcd.clear();
        }

        if (k == 6 ){
          lcd.setCursor(0,0);
          lcd.print("Angulo Gama");
          lcd.setCursor(0,1);
          lcd.print(gama);
          delay(200*clock);
          lcd.clear();
        }
      break;

      case 7:
        lcd.setCursor(0,0);
        lcd.print("Estado do Slave");
        lcd.setCursor(0,1);

        if (estado == true){
          lcd.print("ON");
        }
        else{
          lcd.print("OFF");
        }

        delay(20);
        lcd.clear();
      break;

      default:
       /*Comand*/
      break;
    }
  }

  comand = 0;
  
}