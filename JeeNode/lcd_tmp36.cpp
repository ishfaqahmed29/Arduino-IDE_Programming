/*
	Test code to check following hardware components-
	i) Temperature Sensor, TMP36
	ii) Liquid Crystal I2C Display, HD44780
*/



// Temperature Sensor Setup Code

int reading = analogRead(sensorPin);                // Analog reading obtained from the sensor
float voltage = reading * 5.0;                      // For converting 5V JeeNode's voltage reading
voltage /= 1024.0; 
Serial.print(voltage); 


float temperatureC = (voltage - 0.5) * 100 ;        // Converting to degree Celsius

Serial.print(temperatureC); 
Serial.println(" degrees C");

// LCD Setup Code
// LCD --> I2C 2x16

#include <LiquidCrystal_I2C.h>                      // Library required for the I2C LCD functions

LiquidCrystal_I2C lcd(0x27, 16, 2);                 // Sets up LCD address to 0x27 for a 2x16 display 

void setup()
{
	lcd.begin();                    
	lcd.backlight();                
	lcd.print("RoboSphere");        
	Serial.begin(115200);                           // Sets the speed for serial communication
}

void loop()
{
	int reading = analogRead(sensorPin);            // Analog reading obtained from the sensor in Volts
	
    lcd.setCursor(0, 1); 
    lcd.print("Temp:"); 
    lcd.print(tempC); 
    lcd.print((char)223);                            
    lcd.print("C");
}

// Code to display TMP36 sensor reading on LCD

#include <LiquidCrystal_I2C.h>      
#include <Wire.h>                                   // Library to initialize the JeeNode ports

LiquidCrystal_I2C lcd(0x27, 16, 2);                 

int sensorPin = 0;                                  // Variable to record analog reading

void setup()
{
	lcd.begin();   
	lcd.backlight();    
	lcd.print("RoboSphere");   
	Serial.begin(115200);                           // Sets the speed for serial communication 
}

void loop()
{
	int reading = analogRead(sensorPin); 
	float tempVolts = (reading * 5.0) / 1024.0;     // For 5V power supply, converting with a scale factor of 10mV/deg.C
	float tempC = (tempVolts - 0.5) * 100.0;        // Final temp. value in deg.C after all conversions
  
 	lcd.setCursor(0, 1); 
	lcd.print("Temp:"); 
	lcd.print(tempC); 
	lcd.print((char)223);                           
	lcd.print("C");
}
