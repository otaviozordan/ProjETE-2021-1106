//Projeto: V4 - Projete
//Autor Inicial: Otávio Zordan


#include <LiquidCrystal.h> //Adiciona a biblioteca "LiquidCrystal" ao projeto

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // Pinagem do LCD

String recive; //String para simular comandos da Central Eletronica

const float clock = 4; //Constante multiplicadora para corrigir o atraso do Tinkercad

float hLeve; //Altura Inicial Fronta, Altura Inicial Traseira
float hcarregado; //Altura Medida Frontal, Altura Medida Traseira
float dif; //Diferença Frontal, Diferença Traseira, Difença F-T
float lh, enex; // Altura Padrão do Faról em ralação ao chão, Entre Eixos 
float teta, alpha, gama; //Angulos

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

  Serial.begin(9600); //Inicia monito serial
  lcd.begin(16, 2); // Inicia o lcd de 16x2

  hLeve = 45; 
  lh = 100;
  enex = 379;

  pinMode(9, OUTPUT);
}

void loop() {

  k = analogRead(A0);
  k = map(k, 1, 1023, 1, 6);

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
    delay(20*clock);

    leituraT();
    hLeve = distanceT;

    lcd.setCursor(0,0);
    lcd.print("H padrao traseiro");
    lcd.setCursor(0,1);
    lcd.print(hLeve);
    delay(50*clock);
    lcd.clear();

    Serial.println("As distancias definidas como padrao foram: ");
    Serial.print(hLeve);
    Serial.println(" para T");
    recive = "";
    Serial.println("");
  }

  else if (recive == "Altura do Farol " || comand == 2) {
    if(Serial.available()){  //Verifica a chegada de algo pela serial
      lh = Serial.read();

      lcd.setCursor(5,0);
      lcd.print("H Farol");
      lcd.setCursor(4,1);
      lcd.print(lh);

      Serial.println("Recebemos o valor de:");
      Serial.println(lh);
      recive = "";
      Serial.println("");

      delay(50*clock);
      lcd.clear();
    }
  }

  else if (recive == "Entre Eixos " || comand == 3) {
    if(Serial.available()){  //Verifica a chegada de algo pela serial
      enex = Serial.read();

      lcd.setCursor(3,0);
      lcd.print("Entre Eixo");
      lcd.setCursor(4,1);
      lcd.print(enex);

      Serial.println("Recebemos o valor de:");
      Serial.println(enex);
      recive = "";
      Serial.println("");

      delay(50*clock);
      lcd.clear();
    }
  }

  else if(recive == "Calibracao" || comand == 4){ 
    Serial.println("Iniciando Calibracao");

    lcd.setCursor(3,0);
    lcd.print("Iniciando");
    lcd.setCursor(2,1);
    lcd.print("Calibracao");
    delay(20*clock);
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
    delay(50*clock);
    lcd.clear();

    lcd.setCursor(0,0);
    lcd.print("Angulo Gama");
    lcd.setCursor(0,1);
    lcd.print(gama);
    delay(50*clock);
    lcd.clear();

    lcd.setCursor(1,0);
    lcd.print("Giro no motor");
    lcd.setCursor(0,1);
    lcd.print(gama*360);
    delay(50*clock);
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

    hLeve = 0;

    lcd.print("Valores Zerados");
    delay(50*clock);
    lcd.clear();

    recive = "";
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

      case 4:
        lcd.setCursor(5, 0);
        lcd.print("Fazer");
        lcd.setCursor(3, 1);
        lcd.print("Calibracao");   
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

      case 5:
        lcd.setCursor(3, 0);
        lcd.print("Definir");
        lcd.setCursor(2, 1);
        lcd.print("Valores Zero"); 
        delay(20);
        lcd.clear();  
      break;

      case 6:
        lcd.setCursor(0,0);
        lcd.print("Compressao t de");
        lcd.setCursor(0,1);
        lcd.print(dif);
        delay(50*clock);
        lcd.clear();

        lcd.setCursor(0,0);
        lcd.print("Angulo Gama");
        lcd.setCursor(0,1);
        lcd.print(gama);
        delay(50*clock);
        lcd.clear();
      break;

      default:
       /*Comand*/
      break;
    }
  }

  comand = 0;
  
}
