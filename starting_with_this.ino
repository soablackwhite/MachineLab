#include <Wire.h>                   //stepper library 1
#include <Adafruit_MotorShield.h>  //stepper library 2
#include <Servo.h>                //servo library

int servoPin = 13;                                                     //Pin for the servo's switch, to the right
int stepPin = 12;                                                     //Pin for the stepper's switch.
int servoPin2 = 11;                                                  //Pin for the stepper's switch, to the left
Servo servoMotor;                                                   //instantiation of servo object
int pos = 0;                                                       //current position of servo
Adafruit_MotorShield AFMS = Adafruit_MotorShield();               //create the motor shield object with the default I2C address
Adafruit_StepperMotor *stepMotor = AFMS.getStepper(200, 2);      //conecting a stepper motor 200 steps per revolution to motor port #2


void setup() {
  
  pinMode(servoPin, INPUT);         // to initialize input from the servo's switch
  pinMode(stepPin, INPUT);  
  //to initialize input from the stepper's switch

  Serial.begin(9600);                 //set up Serial library at 9600 bps
  AFMS.begin();                      //create with the default frequency 1.6KHz
  stepMotor->setSpeed(10);          //10rpm speed

  servoMotor.attach(9);           //attaching pin number to servo
}


void loop() {
  int servoVal = digitalRead(servoPin);        //reading servo switch off/on
  int servoVal2 = digitalRead(servoPin2);     //reading servo switch 2 off/on
  int stepVal = digitalRead(stepPin);        //reading stepper switch off/on
  Serial.println(stepVal);
  Serial.println(servoVal);

  if (servoVal == HIGH){                        //if switch on
      stepMotor->step(1, FORWARD, SINGLE);     //move stepper
      }
      
  if (stepVal == HIGH){                     //if switch on
      if (pos<180){                        //if the servo's position is less than 180 degrees
        pos +=1;                          //increment +1 to its position
        servoMotor.write(pos);
        delay(15);
      }
  }

  if (servoVal2== HIGH){                     //if switch 2 on
      if (pos>0){                           //if the servo's position is higher than 180 degrees
        pos -=1;                           //increment -1 to its posSition
        servoMotor.write(pos);
        delay(15);
      }
  }


}
