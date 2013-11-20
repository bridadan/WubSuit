#include <SoftwareSerial.h>
#include <Wire.h> //I2C

SoftwareSerial Xbee(10, 11); // RX, TX

//#define DEBUG //unset if not debugging

#define PRECISION 0x00 //0x00 = 2G, 0x01 = 4A, 0x02 = 8G

#define LEDOUT_ADDR 0x20
#define ACCEL_ADDR 0x1D
#define ACCEL_X_MSB 0x01
#define ACCEL_CTRL 0x2A
#define ACCEL_XYZCFG 0x0E

#define PIEZO_L A0
#define PIEZO_R A1
#define FLEX_L A2
#define FLEX_R A3

#define SONAR 7
#define LEDPIN 13
#define TAP_L 3
#define TAP_R 4

#define FLEX_LOW 200
#define FLEX_HIGH 500
#define SONAR_LOW 0
#define SONAR_HIGH 72
#define THRESHOLD 950

byte Ax = 0x00;
byte Ay = 0x00;
byte Az = 0x00;
byte flex = 0x00;
byte height = 0x00;

void setup()  
{
  Wire.begin(); //i2c master
  //initMMA8452(); //initialize accelerometer
  
  // Open local serial port for debugging:
  Serial.begin(115200);

  // Open XBee serial for mass data communication
  Xbee.begin(115200);
  
  //Configure pins
  pinMode(LEDPIN,OUTPUT);
  pinMode(SONAR,INPUT);
  pinMode(TAP_L,OUTPUT);
  
  //turn the default 0xFF LEDs to all off
  setLEDs(0x00);
  
  //init accel
  initAccel();
}

void loop()
{

  updateAccel(Ax,Ay,Az);
  
  //write every recieved xbee byte to the leds
  if (Xbee.available()){
    setLEDs(Xbee.read());
  }
  
  if(analogRead(PIEZO_L) < THRESHOLD){
    Serial.println("Left tap");
    pulse(TAP_L);
  }
  
  height = map(pulseIn(SONAR,HIGH)/147,SONAR_LOW,SONAR_HIGH,0,255);
  flex = map(analogRead(FLEX_L),FLEX_LOW,FLEX_HIGH,0,255);
  sendPacket();
}

void setLEDs(byte data){
  //Writes a byte to the LED strip via i2c
    Wire.beginTransmission(LEDOUT_ADDR);
    Wire.write(data);
    Wire.endTransmission();
}

void sendPacket(){
  //send a packet of data to UART 
  Xbee.write((byte)0x00);
  Xbee.write(Ax);
  Xbee.write(Ay);
  Xbee.write(Az);
  Xbee.write(flex);
  Xbee.write(height);
}

void pulse(int pin){
 //pulses a pin for one cycle
 //assumes pin is declared as output
 digitalWrite(pin, HIGH);  
 delay(10);
 digitalWrite(pin, LOW); 
}

void initAccel(){
  //first we get the status of the ctrl reg
  Wire.beginTransmission(ACCEL_ADDR);
  Wire.write(ACCEL_CTRL);
  Wire.endTransmission(false); //waits for data
  Wire.requestFrom(ACCEL_ADDR,1);
  while(!Wire.available()); //hang out until available
  byte ctrl = Wire.read();
  
  //now we throw it in standby to edit ctrl reg
  Wire.beginTransmission(ACCEL_ADDR);
  Wire.write(ACCEL_CTRL);
  Wire.write(ctrl & ~(0x01)); //clears active bit
  Wire.endTransmission();
  
  //write the scale
  Wire.beginTransmission(ACCEL_ADDR);
  Wire.write(ACCEL_XYZCFG);
  Wire.write(PRECISION); //set precision
  Wire.endTransmission();
  
  //throw it back into active
  Wire.beginTransmission(ACCEL_ADDR);
  Wire.write(ACCEL_CTRL);
  Wire.write(ctrl | 0x01); //sets active bit, if not set
  Wire.endTransmission();
}

void updateAccel(byte &x,byte &y,byte &z){
  byte data[6];
  Wire.beginTransmission(ACCEL_ADDR);
  Wire.write(ACCEL_X_MSB);
  Wire.endTransmission(false); //this ends the write, but waits for the response
  
  Wire.requestFrom(ACCEL_ADDR,6); //6 bytes: Xhigh,low Yhigh,low Zhigh,low
  while(Wire.available() < 6){}; //wait until they all appear in the buffer
  
  for(int i=0; i<6; i++)
    data[i] = Wire.read(); //empty the buffer into the data array
   
   #ifdef DEBUG 
     Serial.print("X: 0x");
     Serial.print(data[5],HEX);
     Serial.print(data[4],HEX);
     Serial.print(" Y: 0x");
     Serial.print(data[3],HEX);
     Serial.print(data[2],HEX);
     Serial.print(" Z: 0x");
     Serial.print(data[1],HEX);
     Serial.println(data[0],HEX);
   #endif
   
   x = data[5];
   y = data[3];
   z = data[1];
}
