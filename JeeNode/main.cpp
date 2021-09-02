/*
    Code to test the design
*/

#include <Adafruit_PWMServoDriver.h>
#include <Adafruit_MotorShield.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>       
#include "Adafruit_PWMServoDriver.h"


// Create motorshield object 
AFMS = 0x61 I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// 200 step motors connected to shield's motor ports(1 = M1 & M2, 2 = (M3 & M4) 
Adafruit_StepperMotor *myMotor_one = AFMS.getStepper(48, 1);
Adafruit_StepperMotor *myMotor_two = AFMS.getStepper(48, 2);

/*
    Global Variables     
*/

unsigned long time_since_last_reset = 0;   

int interval_one   = 2000;        //2 seconds   
int interval_two   = 3000;        
int interval_three = 4000;        
int interval_four  = 5000;        
int interval_five  = 6000;        
int interval_six   = 7750;         
int ledPin_one = 13;             
int ledPin_two = 12;               	
int ledPin_three= 8;               	
int inputPin_one= 2;               	
int inputPin_two = 6;              	
int inputPin_three = 4;            	
int pirState_one= LOW;             	
int pirState_two = LOW;            	
int pirState_three = LOW;          
int val_one = 0;                   	
int val_two = 0;
int val_three = 0;

void setup() {
    
    AFMS.begin();        		
   
    myMotor_one->setSpeed(10);   		
    myMotor_two->setSpeed(10);   		
    pinMode(ledPin_one, OUTPUT);  	
    pinMode(inputPin_one, INPUT);		
    pinMode(ledPin_two, OUTPUT);		
    pinMode(inputPin_two, INPUT);		
    pinMode(ledPin_three, OUTPUT);	
    pinMode(inputPin_three, INPUT);	
    
    Serial.begin(9600);
}

void loop() {

  val_one = digitalRead(inputPin_one);  
  val_two = digitalRead(inputPin_two);
  val_three = digitalRead(inputPin_three);
  time_since_last_reset = millis();
  pir(ledPin_one, pirState_one, val_one, 1);
  time_since_last_reset = millis();
  pir(ledPin_two, pirState_two, val_two,2);
  delay(500);
  time_since_last_reset = millis();
  pir(ledPin_three, pirState_three, val_three, 3);
  delay(1000);

}

void pir(int ledPin, int pirState, int val, int motor) {
    
    if (val == HIGH) {
        digitalWrite(ledPin, HIGH);    
        while ((millis() - time_since_last_reset) < interval_five) { 
            for (int i = 0; i < 200; i++) {
                if (motor == 1) {
                    myMotor_two->step(1, FORWARD, SINGLE);          // Single coil actuation
                    Serial.println("Motion sensor 2 led 13 right");
                }
                if (motor == 2 ) {
                    myMotor_one->step(1, BACKWARD, SINGLE);      
                    Serial.println("Motion sensor 6 led 12 left ");
                }
                if (motor == 3) {
                    myMotor_one->step(1, BACKWARD, SINGLE);
                    myMotor_two->step(1, FORWARD, SINGLE);
                    Serial.println("Motion sensor 4 led 8 center");
                    delay(1000);
                }
            }
        }
        // Step each time through for 
        if (pirState == LOW) {
            Serial.println("Motion detected!");
            pirState = HIGH;
        }
    }
    else {
        digitalWrite(ledPin, LOW); 
        if (pirState == HIGH) {
        Serial.println("Motion ended!");
        pirState = LOW;
        }
    }
}
