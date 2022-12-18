#include <Key.h>
#include <Keypad.h>

#include <LiquidCrystal.h>

const int flamePin = 0;
const int buzzPin = 13;

const int pirPin = 1;
const int lampPin = 12;

const int tempPin = A0;

const int lcdRs = 10;
const int lcdE = 9;
const int lcdD4 = 4;
const int lcdD5 = 5;
const int lcdD6 = 6;
const int lcdD7 = 7;

LiquidCrystal lcd(lcdRs, lcdE, lcdD4, lcdD5, lcdD6, lcdD7);

char tuslar[4][3]= {
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'},
    {'*','0','#'}
  };

byte rowPins[4] = {29, 30, 31, 32};
byte colPins[3] = {24, 23, 22};

char okunanPass[5];
char masterPass[5] = {"9685"};
byte dataCount = 0;

const int keyRedPin = 47;
const int keyGreenPin = 48;

Keypad keyPad = Keypad(makeKeymap(tuslar), rowPins, colPins, 4, 3);

unsigned long sonCalisma=0;
unsigned long yeniCalisma;

void setup() {
  // put your setup code here, to run once:
  pinMode(flamePin, INPUT);
  pinMode(buzzPin, OUTPUT);
  pinMode(pirPin, INPUT);
  pinMode(lampPin, OUTPUT);
  pinMode(keyRedPin, OUTPUT);
  pinMode(keyGreenPin, OUTPUT);

  lcd.begin(16, 2);
}

void loop() {
  // put your main code here, to run repeatedly:

  //flame sensor
  if(digitalRead(flamePin)){
      digitalWrite(buzzPin, HIGH);
    }
    else{
      digitalWrite(buzzPin, LOW);
      }


   //pir sensor
   if(digitalRead(pirPin)){
      digitalWrite(lampPin, HIGH);
    }
    else{
      digitalWrite(lampPin, LOW);
      }


   //lcd
   yeniCalisma = millis();
   if(yeniCalisma>1000+sonCalisma){
      lcd.clear();
      sonCalisma = yeniCalisma;
      lcd.print("Sicaklik:");
      float temp = analogRead(tempPin);
      float ftemp = (temp/1023.0)*500;
      int ctemp = ftemp;
      lcd.print(ctemp);
      lcd.print("*C");
      if(ctemp <= 20){
          lcd.setCursor(0, 1);
          lcd.print("Dustu");
        }
      else if(ctemp >= 30){
          lcd.setCursor(0, 1);
          lcd.print("Yukseldi");
          }
   //delay(1000);
      //lcd.clear();
   }

   
   //Keypad
   char okunanTus = keyPad.getKey();
   if(okunanTus){
    okunanPass[dataCount] = okunanTus;
    dataCount++;
    }
    if(dataCount == 4){
        if(!strcmp(masterPass, okunanPass)){
          digitalWrite(keyRedPin, LOW);
          digitalWrite(keyGreenPin, HIGH);
          }
        else{
          digitalWrite(keyGreenPin, LOW);
          digitalWrite(keyRedPin, HIGH);
          }
        for(int i=0 ;i<4; i++){
          okunanPass[i]= -1;
          }
         dataCount = 0;
      }
   
}
