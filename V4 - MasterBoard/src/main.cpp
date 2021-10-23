//Projeto: V4 - Projete
//Autor Inicial: Otávio Zordan


#include <LiquidCrystal.h> //Adiciona a biblioteca "LiquidCrystal" ao projeto

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // Pinagem do LCD

String recive; //String para simular comandos da Central Eletronica

float hif, hit; //Altura Inicial Fronta, Altura Inicial Traseira
float hmf, hmt; //Altura Medida Frontal, Altura Medida Traseira
float diff, dift, dif; //Diferença Frontal, Diferença Traseira, Difença F-T
float lh,eeix ; // Altura Padrão do Faról em ralação ao chão, Entre Eixos 

int k, comand; //k para mostrar no lcd e comand para executar as configurações

bool menu; //Estado de seleção do menu

// Para leitura:
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

void setup(){
  pinMode(trigPin1, OUTPUT); //Define os pinos do ultrassonico 1
  pinMode(echoPin1, INPUT);

  pinMode(trigPin2, OUTPUT); //Define os pinos do ultrassonico 2
  pinMode(echoPin2, INPUT);

  Serial.begin(9600); //Inicia monito serial
  lcd.begin(16, 2); // Inicia o lcd de 16x2
  
}

void loop() {

  k = analogRead(A0); //Leitura da posição do potenciometro
  k = map(k, 1, 1023, 1, 5); //Converção para a lista do menu

  if (digitalRead(10)==1 && menu == false){  //Libera acesso ao menu
    lcd.setCursor(2, 0);
    lcd.print("Aguarde para");
    lcd.setCursor(6, 1);
    lcd.print("Menu");
    delay(500);

    if (digitalRead(10)==1){
      menu = true
      lcd.clear();
      Serial.println("Entrando em menu")
      Serial.println("");
    }
    else{
      lcd.clear();
      Serial.println("Modo exibicao");
      Serial.println("");
    }
  }

  if(digitalRead(10) == 1 && menu == true){ //Trasfere a mensagem no lcd para comando no menu
    comand = k ;
    Serial.println("Selecionado");
    Serial.println("");
  }
  
  if(Serial.available()){  //Verifica a chegada de algo pela serial
    recive = Serial.readString(); //Realiza a importação de comandos de debug pelo serial
    Serial.println("Comando recebido");
    Serial.println("");
  }   
  
  while (menu){

    if(recive == "Definir Altura Padrao" || comand == 1){ //Para fazer a leitura - SetHigh 
      Serial.println("Iniciando SetHigh");

      lcd.setCursor(4,0);
      lcd.print("Definido");
      lcd.setCursor(2,1);
      lcd.print("Altura Padrao");
      delay(200);

      leituraT();
      leituraF();
      hif = distanceF;
      hit = distanceT;

      lcd.setCursor(0,0);
      lcd.print("H padrão traseiro");
      lcd.setCursor(0,1);
      lcd.print(hit);
      delay(500);
      lcd.clear();

      lcd.setCursor(0,0);
      lcd.print("H padrão frontal");
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
      Serial.println("");
    }

    else if(recive == "Calibracao" || comand == 2){ 
      Serial.println("Iniciando Calibração");

      lcd.setCursor(5,0);
      lcd.print("Start");
      lcd.setCursor(3,1);
      lcd.print("Calibrate");
      delay(200);
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
      delay(300);
      lcd.clear();

      lcd.setCursor(0,0);
      lcd.print("Comprecao f de");
      lcd.setCursor(0,1);
      lcd.print(diff);
      delay(300);
      lcd.clear();

      lcd.setCursor(0,0);
      lcd.print("Diferenca de: ");
      lcd.setCursor(0,1);
      lcd.print(dif);
      delay(300);
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
      Serial.println("");   
    }

    else if (recive == "H Farol " || comand == 3) {
      if(Serial.available()){  //Verifica a chegada de algo pela serial
        lh = Serial.read();

        lcd.setCursor(5,0);
        lcd.print("H Farol");
        lcd.setCursor(4,1);
        lcd.print(lh);
        delay(200);

        Serial.println("Recebemos o valor de:");
        Serial.println(lh);
        recive = "";
        Serial.println("");
      }
    }

    else if(recive == "Entre Eixos" || comand == 4){ 
      Serial.println("Zerando Valores");
      hif = 0;
      hit = 0;
      Serial.println(""); 
      recive = "";
    }

    else if(recive == "Zerar" || comand == 5){ 
      Serial.println("Zerando Valores");
      hif = 0;
      hit = 0;
      Serial.println(""); 
      recive = "";
    }

    else{
      switch (k){
      case 1:
        lcd.setCursor(3, 0);
        lcd.print("Definir");
        lcd.setCursor(2, 1);
        lcd.print("Altura Padrao"); 
        delay(5);
        lcd.clear();  
      break;

      case 2:
        lcd.setCursor(5, 0);
        lcd.print("Fazer");
        lcd.setCursor(3, 1);
        lcd.print("Calibracao");   
        delay(5);
        lcd.clear();    
      break;    

      case 3:
        lcd.setCursor(1, 0);
        lcd.print("Definir Altura");
        lcd.setCursor(4, 1);
        lcd.print("do Farol"); 
        delay(5);
        lcd.clear();   
      break;

      case 4:
        lcd.setCursor(3, 0);
        lcd.print("Definir");
        lcd.setCursor(2, 1);
        lcd.print("Entre Eixos"); 
        delay(5);
        lcd.clear();   

      case 5:
        lcd.setCursor(3, 0);
        lcd.print("Definir");
        lcd.setCursor(2, 1);
        lcd.print("Valores Zero"); 
        delay(5);
        lcd.clear();   
      break;  

      default:
        //***Comand**
      break;
      }
      comand = 0;
    }
    menu = !digitalRead(10);
  }
}
