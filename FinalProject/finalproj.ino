#include <LiquidCrystal.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <EEPROM.h>

const int rs = 10, en = 9, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_StepperMotor *myMotor = AFMS.getStepper(200, 2);
Adafruit_DCMotor *myDotor = AFMS.getMotor(1);

unsigned long tim, ctim, htim;
int e = 0;
int on = 0;
char buf[16];

void setup() {
  EEPROM.get(0,htim);
  Serial.begin(9600);
  Serial.print("High Score: ");
  Serial.println(htim);
  
  lcd.begin(16, 2);
  lcd.print("HIGH SCORE:");
  tim = htim;
  int ms = tim%1000, s = (tim-ms)/1000%60, m = (tim-ms)/60000;
  sprintf(buf,"%d:%02d.%03d",m,s,ms);
  lcd.setCursor(0,1);
  lcd.print(buf);

  AFMS.begin();
  myMotor->setSpeed(100);
  myDotor->setSpeed(50);

  pinMode(8,INPUT);
  pinMode(6,OUTPUT);
  pinMode(12,INPUT);
}

void loop() {
  if(digitalRead(12)) on = 1, ctim = millis();
  if(on){
    if(digitalRead(8)){;
      lcd.setCursor(0,0);
      lcd.print("GAME OVER!");
      on = 0;
      Serial.println(buf);
      if(tim > htim){
        EEPROM.put(0,tim);
        lcd.setCursor(0,0);
        lcd.print("NEW HIGH SCORE!");
        Serial.println("New high score");
        EEPROM.get(0,htim);
        Serial.println(htim);
      }
    } else {
      lcd.setCursor(0,0);
      lcd.print("TIME             ");
      tim = millis()-ctim;
      int ms = tim%1000, s = (tim-ms)/1000%60, m = (tim-ms)/60000;
      sprintf(buf,"%d:%02d.%03d",m,s,ms);
      lcd.setCursor(0,1);
      lcd.print(buf);
      lcd.print("      ");
    
      myMotor->step(1,BACKWARD,MICROSTEP);
      myDotor->run(FORWARD);
      digitalWrite(6,HIGH);
    }
  } else digitalWrite(6,LOW), myDotor->run(RELEASE);
}
