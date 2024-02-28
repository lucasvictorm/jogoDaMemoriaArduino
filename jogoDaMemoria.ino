#include <time.h>;
#include <stdlib.h>;
#include <Wire.h>;
#include <LiquidCrystal_I2C.h>;

const int LedPin1 = 13;
const int LedPin2 = 10;
const int LedPin3 = 11;
const int LedPin4 = 12;
const int Btn1 = 2;
const int Btn2 = 3;
const int Btn3 = 5;
const int Btn4 = 6;

int EstadoBtn1 = 0;
int EstadoBtn2 = 0;
int EstadoBtn3 = 0;
int EstadoBtn4 = 0;

int posArray = 0;
int luzes[20];
int aleatorio = 0;
int size = 0;
int jogada = 2;
int posAtual = 0;
bool game = false;
int nivel = 0;
bool botaoApertado = false;
int modo = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2);
const int Buzzer = 9;

int telaAtual = 1;

void erro() {
  for (int i = 0; i < 10; i++) {
    luzes[i] = 0;
  }
  game = false;
  jogada = 2;

  posArray = 0;
  nivel = 0;
  digitalWrite(LedPin1, HIGH);
  digitalWrite(LedPin2, HIGH);
  digitalWrite(LedPin3, HIGH);
  digitalWrite(LedPin4, HIGH);
  EstadoBtn1 = LOW;

  delay(500);
  digitalWrite(LedPin1, LOW);
  digitalWrite(LedPin2, LOW);
  digitalWrite(LedPin3, LOW);
  digitalWrite(LedPin4, LOW);
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Voce perdeu!");
  digitalWrite(Buzzer, HIGH);
  tone(Buzzer, 87, 1000);
  delay(800);


  digitalWrite(Buzzer, LOW);
  noTone(Buzzer);
  delay(1200);
  lcd.clear();
}

void sortear() {
 
  size = 0;
  
  aleatorio = random(1, 5);

  do {
    int numOk = luzes[size];
    if (numOk == 0) {
      break;
    }


    size++;

  } while (true);

  if (luzes[size - 1] != aleatorio || size == 0) {
    size++;
    Serial.println(luzes[posArray]);
    luzes[posArray] = aleatorio;
  } else {
    sortear();
  }
}

void sortearRepete() {
  size = 0;
  //aleatorio = 1 + rand() % (1-4);
  aleatorio = random(1, 5);

  do {
    int numOk = luzes[size];
    if (numOk == 0) {
      break;
    }


    size++;

  } while (true);


  size++;
  Serial.println(luzes[posArray]);
  luzes[posArray] = aleatorio;
}



void setup() {
  // put your setup code here, to run once:
  pinMode(LedPin1, OUTPUT);
  pinMode(LedPin2, OUTPUT);
  pinMode(LedPin3, OUTPUT);
  pinMode(LedPin4, OUTPUT);
  pinMode(Btn1, INPUT);
  pinMode(Btn2, INPUT);
  pinMode(Btn3, INPUT);
  pinMode(Btn4, INPUT);
  pinMode(Buzzer, OUTPUT);
  Serial.begin(9600);
  randomSeed(analogRead(0));
  lcd.init();
}


void loop() {
  lcd.setBacklight(HIGH);


  // put your main code heuzere, to run repeatedly:
  EstadoBtn1 = digitalRead(Btn1);
  EstadoBtn2 = digitalRead(Btn2);
  EstadoBtn3 = digitalRead(Btn3);
  EstadoBtn4 = digitalRead(Btn4);
  //Serial.println(EstadoBtn1);
  //delay(500);


  if (jogada == 2) {

    if (telaAtual == 1) {
      lcd.setCursor(3, 0);
      lcd.print("Nivel Facil");

      if (EstadoBtn4 == HIGH) {
        delay(500);
        lcd.clear();
        telaAtual = 2;
      }
      if (EstadoBtn3 == HIGH) {
        delay(500);
        lcd.clear();
        telaAtual = 3;
      }
      if (EstadoBtn1 == HIGH) {
        modo = 1;
        jogada = 0;
      }
    }

    else if (telaAtual == 2) {
      telaAtual = 2;

      lcd.setCursor(3, 0);
      lcd.print("Nivel Medio");
      if (EstadoBtn4 == HIGH) {
        delay(500);
        lcd.clear();
        telaAtual = 3;
      }
      if (EstadoBtn3 == HIGH) {
        delay(500);
        lcd.clear();
        telaAtual = 1;
      }
      if (EstadoBtn1 == HIGH) {
        modo = 2;
        jogada = 0;
      }

    }

    else if (telaAtual == 3) {
      telaAtual = 3;


      lcd.setCursor(2, 0);
      lcd.print("Nivel Dificil");
      if (EstadoBtn4 == HIGH) {
        delay(500);
        lcd.clear();
        telaAtual = 1;
      }
      if (EstadoBtn3 == HIGH) {
        delay(500);
        lcd.clear();
        telaAtual = 2;
      }

      if (EstadoBtn1 == HIGH) {
        modo = 3;
        jogada = 0;
      }
    }
  }


  if (jogada == 1) {

    if (posAtual < size) {

      if (EstadoBtn1 == HIGH) {
    


        digitalWrite(LedPin1, HIGH);



        if (luzes[posAtual] == 1) {
          Serial.println(luzes[posAtual]);

          posAtual++;
          delay(400);
        } else {
          erro();
        }
      } else {
        //botaoApertado = false;
        digitalWrite(LedPin1, LOW);
      }



      if (EstadoBtn2 == HIGH) {
        digitalWrite(LedPin2, HIGH);



        if (luzes[posAtual] == 2) {

          posAtual++;

          delay(400);
        } else {
          erro();
        }


      } else {
        digitalWrite(LedPin2, LOW);
      }


      if (EstadoBtn3 == HIGH) {
        digitalWrite(LedPin3, HIGH);


        if (luzes[posAtual] == 3) {

          posAtual++;
          delay(400);
        } else {
          erro();
        }

      } else {
        digitalWrite(LedPin3, LOW);
      }


      if (EstadoBtn4 == HIGH) {
        digitalWrite(LedPin4, HIGH);


        if (luzes[posAtual] == 4) {

          posAtual++;
          delay(400);
        } else {
          erro();
        }

      } else {
        digitalWrite(LedPin4, LOW);
      }


    } else {
      game = true;
      jogada = 0;
    }
  }

  if (jogada == 0) {
    digitalWrite(LedPin1, LOW);
    digitalWrite(LedPin2, LOW);
    digitalWrite(LedPin3, LOW);
    digitalWrite(LedPin4, LOW);

    if (nivel == 10 && modo == 1 || nivel == 15 && modo == 2 || nivel == 20 && modo == 3) {
      for (int i = 0; i < 600; i++) {
        digitalWrite(Buzzer, HIGH);
        delayMicroseconds(100);
        // tone(Buzzer, 1000);

        digitalWrite(Buzzer, LOW);
        delayMicroseconds(100);
      }
      for (int i = 0; i < 600; i++) {
        digitalWrite(Buzzer, HIGH);
        delayMicroseconds(200);
        // tone(Buzzer, 1000);

        digitalWrite(Buzzer, LOW);
        delayMicroseconds(200);
      }

      for (int i = 0; i < 600; i++) {
        digitalWrite(Buzzer, HIGH);
        delayMicroseconds(300);
        // tone(Buzzer, 1000);

        digitalWrite(Buzzer, LOW);
        delayMicroseconds(300);
      }


      lcd.clear();
      lcd.setCursor(4, 0);

      lcd.print("Parabens!");
     
      if(modo == 3){
        lcd.clear();
         lcd.setCursor(2, 0);
        lcd.print("Nivel Dificil");

        lcd.setCursor(3,1);
        lcd.print("Ganhou R$50");
      }else{
          lcd.setCursor(3, 1);
      lcd.print("Voce venceu");
      }
       
      for(int i = 0; i < 4; i++){
        digitalWrite(LedPin1, HIGH);
        delay(500);
        digitalWrite(LedPin1, LOW);
        digitalWrite(LedPin2, HIGH);
        delay(500);
        digitalWrite(LedPin2, LOW);
        digitalWrite(LedPin3, HIGH);
        delay(500);
        digitalWrite(LedPin3, LOW);
        digitalWrite(LedPin4, HIGH);
        delay(500);
        digitalWrite(LedPin4, LOW);
      }

      
      game = false;
      posArray = 0;
      for (int i = 0; i < 10; i++) {
        luzes[i] = 0;
      }
      nivel = 0;
      lcd.clear();
      jogada = 2;
    }


    if (EstadoBtn1 == HIGH || game) {


      nivel++;
      //Serial.println(nivel);

      delay(500);

      if (nivel == 1) {

        lcd.clear();
        digitalWrite(Buzzer, HIGH);
        tone(Buzzer, 98, 500);
        delay(500);
        tone(Buzzer, 247, 500);
        delay(500);
        tone(Buzzer, 294, 500);
        delay(500);
        digitalWrite(Buzzer, HIGH);
        noTone(Buzzer);
      }


      if (nivel == 10) {
        lcd.clear();
        lcd.setCursor(5, 0);
        lcd.print("Nivel");
        lcd.setCursor(6, 1);
        lcd.print(nivel);
      } else {
        lcd.clear();
        lcd.setCursor(5, 0);
        lcd.print("Nivel");
        lcd.setCursor(7, 1);
        lcd.print(nivel);
      }

      if(modo == 1){
        sortear();
      }else{
        sortearRepete();
      }
      
      for (int i = 0; i < size; i++) {
        if (luzes[i] == 1) {
          digitalWrite(LedPin1, HIGH);
          delay(300);
          digitalWrite(LedPin1, LOW);
          delay(300);
        } else if (luzes[i] == 2) {
          digitalWrite(LedPin2, HIGH);
          delay(300);
          digitalWrite(LedPin2, LOW);
          delay(300);
        } else if (luzes[i] == 3) {
          digitalWrite(LedPin3, HIGH);
          delay(300);
          digitalWrite(LedPin3, LOW);
          delay(300);
        } else if (luzes[i] == 4) {
          digitalWrite(LedPin4, HIGH);
          delay(300);
          digitalWrite(LedPin4, LOW);
          delay(300);
        }
      }
      posAtual = 0;
      jogada = 1;
      game = false;
      posArray++;

      delay(200);
    } else {
      digitalWrite(LedPin1, LOW);
      digitalWrite(LedPin2, LOW);
      digitalWrite(LedPin3, LOW);
      digitalWrite(LedPin4, LOW);
    }
  }
}
