#include <SoftwareSerial.h>
#include <Wire.h> //I2C
//#include <./MMA8452.h> //accel

SoftwareSerial mySerial(10, 11); // RX, TX

#define LEDPIN 13
#define LEDOUT_ADDR 0x20


void setup()  
{
  Wire.begin(); //i2c master
  //initMMA8452(); //initialize accelerometer
  
  // Open local serial port for debugging:
  Serial.begin(115200);

  // Open XBee serial for mass data communication
  mySerial.begin(115200);
  
  //Configure pins as outputs
  pinMode(LEDPIN,OUTPUT);
}

void loop()
{
  //if (mySerial.available())    
   // Serial.write(mySerial.read());
  if (mySerial.available()){
    byte data = mySerial.read();
    Wire.beginTransmission(LEDOUT_ADDR);
    Wire.write(data);
    Serial.write(data);
    Wire.endTransmission();
  } 
}

