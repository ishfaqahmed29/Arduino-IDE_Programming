/*
  Code for JeeNode Micrcontroller - RF Transmitter, RF Receiver and I2C Display
*/

// RF Transmitter and LCD

#include <JeeLib.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

PortI2C myI2C = (2);

LiquidCrystal_I2C lcd = (0x27, 16, 2);                  // Sets the LCD address to 0x27 for a 16 chars and 2 line display
int sensorPin = 2;
Port port1 = Port(1);
Port port2 = Port(4);


void setup()
{
  lcd.begin();
  lcd.backlight();
  lcd.print("RoboSphere");
  Serial.begin(115200);
  Serial.println("JeeNode RF Transmitter");
  rf12_initialize(2, RF12_915MHZ, 212); 		            // Initializes RF: group-212, node-2
  port1.mode2(INPUT);
  port2.mode2(INPUT);
}

void loop()
{
  int lux_value[2];
  
  lux_value[0] = port1.digiRead();			                // Read the lux_value from LDR pin
  lux_value[1] = port2.digiRead();
  Serial.println("1:");
  Serial.println(lux_value[0]);
  Serial.println("2:");
  Serial.println(lux_value[1]);
  while(!rf12_canSend()) rf12_recvDone();		            // Wait for any receiving to finish
  rf12_sendStart(0, &lux_value,sizeof(lux_value)); 	    // Getting voltage reading from temperature sensor

  delay(50);

  //Temperature Sensor
  int reading = analogRead(sensorPin);
  
  float voltage = reading * 3.3;
  voltage /= 1024.0;
  
  float temperatureC = (voltage - 0.5) * 100 ;
  
  lcd.setCursor(0,1);
  lcd.print(temperatureC);
  lcd.print(" degrees C");

  delay(100);   // ~ 1sec delay

  return 0;
}

// RF Receiver
#include <JeeLib.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

Port port1 = Port(1);
Port port2 = Port(4);


void setup()
{
  Serial.begin(115200);
  Serial.println("JeeNode RF Receiver");
  rf12_initialize(3, RF12_915MHZ, 212); 		        // Initialize RF: group-212, node-3
  port1.mode(OUTPUT);
  port2.mode(OUTPUT);
}

void loop()
{
  int lux_value[2];
  Serial.println("...");

  if(rf12_recvDone())
  {
    // Wait for any receiving to be done
    int temp[2];
    memcpy(&temp, (int*)rf12_data, sizeof(temp));
    lux_value[0] = temp[0];
    lux_value[1] = temp[1];

    Serial.println(lux_value[0]);
    Serial.println(lux_value[1]);

    if (lux_value[0] == 1)
    {
      port1.digiWrite(HIGH);
    }
    else if (lux_value[1] == 1)
    {
      port2.digiWrite(HIGH);
    }
    else
    {
      port1.digiWrite(LOW);
      port2.digiWrite(LOW);
    }
  }
  
  delay(100);   // ~ 1sec delay
  
  return 0;
}
