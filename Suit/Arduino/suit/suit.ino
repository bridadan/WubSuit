#include <SimpleTimer.h>

#include <SoftwareSerial.h>
#include <Wire.h> //I2C
#include <avr/wdt.h>

SoftwareSerial Xbee(10, 11); // RX, TX
SimpleTimer timer;

#define DEBUG //unset if not debugging

#define PRECISION 0x01 //0x00 = 2G, 0x01 = 4G, 0x02 = 8G

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
#define TAP_L 2
#define TAP_R 3

#define FLEX_LOW 200
#define FLEX_HIGH 500
#define SONAR_LOW 0
#define SONAR_HIGH 72
#define THRESHOLD 50

byte Ax = 0x00;
byte Ay = 0x00;
byte Az = 0x00;
byte flex = 0x00;
byte height = 0x00;

boolean accel = true;

void setup()  
{
  Wire.begin(); //i2c master A5:SCL A4:SDA
  timer.setInterval(30,sendPacket);
  
  // Open local serial port for debugging:
  Serial.begin(115200);

  // Open XBee serial for mass data communication
  Xbee.begin(115200);
  
  //Configure pins
  pinMode(LEDPIN,OUTPUT);
  pinMode(SONAR,INPUT);
  pinMode(TAP_L,OUTPUT);
  pinMode(TAP_R,OUTPUT);
  
  //turn the default 0xFF LEDs to all off
  setLEDs(0x00);
  
  //enable the arduino watchdog for 5 seconds.
  wdt_enable (WDTO_4S);
  
  //init accel
  initAccel();
}

void loop()
{
  timer.run();
  printDebug();
  updateAccel(Ax,Ay,Az);
  
  //write every recieved xbee byte to the leds
  while(Xbee.available()){
    setLEDs(Xbee.read());
  }
  int tap = 0;
  if((tap=analogRead(PIEZO_L)) > THRESHOLD){
    Serial.print("Left tap: ");
    Serial.println(tap);
    pulse(TAP_L);
    pulse(LEDPIN);
  }
  
  if((tap=analogRead(PIEZO_R)) > THRESHOLD){
    Serial.print("Right tap: ");
    Serial.println(tap);
    pulse(TAP_R);
    pulse(LEDPIN);
  }
  byte lastheight = height;
  height = map(pulseIn(SONAR,HIGH,10000)/147,SONAR_LOW,SONAR_HIGH,0,254);
  if(height == 0)
    height = lastheight; //pulseIn broke, so keep valid data.
  flex = map(analogRead(FLEX_L),FLEX_LOW,FLEX_HIGH,0,254);
}

void setLEDs(byte data){
  //Writes a byte to the LED strip via i2c
    Wire.beginTransmission(LEDOUT_ADDR);
    Wire.write(data); //active high
    Wire.endTransmission();
    
    #ifdef DEBUG
      Serial.print("Wrote LEDs to: ");
      Serial.println((byte)(data),BIN);
    #endif
}

void sendPacket(){
  wdt_reset(); //pat the dog to avoid restarting
  //send a packet of data to UART 
  noInterrupts();
  Xbee.write((byte)0xFF);
  Xbee.write((byte)0xA0);
  Xbee.write((byte)0xB7);
  Xbee.write(Ax);
  Xbee.write(Ay);
  Xbee.write(Az);
  Xbee.write(flex);
  Xbee.write(height);
  interrupts();
}

void pulse(int pin){
 //pulses a pin for one cycle
 //assumes pin is declared as output
 digitalWrite(pin, HIGH);  
 delay(10);
 digitalWrite(pin, LOW); 
}

void initAccel(){
  //make sure the accelerometer is actually there
  byte whoamI = 0x00;
  Wire.beginTransmission(ACCEL_ADDR);
  Wire.write(0x0D);
  Wire.endTransmission(false); //waits for data
  Wire.requestFrom(ACCEL_ADDR,1);
  for(int i=0;(i<1000) && !Wire.available();i++); //hang out
  whoamI = Wire.read();
  
  if(whoamI != 0x2A){
    accel = false;
    Serial.println("Accelerometer not available.");
    return;
  }
  
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
  if(!accel) return; //accel not available
  //pulls data from the accelerometer on the I2C bus
  //and places it into the x, y, and z parameters
  byte data[6];
  Wire.beginTransmission(ACCEL_ADDR);
  Wire.write(ACCEL_X_MSB);
  Wire.endTransmission(false); //this ends the write, but waits for the response
  
  Wire.requestFrom(ACCEL_ADDR,6); //6 bytes: Xhigh,low Yhigh,low Zhigh,low
  while(Wire.available() < 6){}; //wait until they all appear in the buffer
  
  for(int i=0; i<6; i++){
    data[i] = Wire.read(); //empty the buffer into the data array
    if(data[i] == 0xFF) //don't invalizate packet structure
      data[i] = 0xFE;
  }
  
   //x = map((data[0]<<8 | data[1])/2,0,0xFFFF,0,0xFE);
   //y = map((data[2]<<8 | data[3])/2,0,0xFFFF,0,0xFE);
   //z = map((data[4]<<8 | data[5])/2,0,0xFFFF,0,0xFE);
   x = data[0];
   y = data[2];
   z = data[4];
}

void printDebug(){
  if(Serial.available()){
   //process debug data first
   char input = Serial.read(); //r: flexR, l: flexL, x:accelX, y,z same, w(char) write LED,
   switch(input){
    case 'r':
      Serial.println(analogRead(FLEX_R));
      break;
    case 'l':
      Serial.println(analogRead(FLEX_L));
      break;
    case 'x':
      Serial.println(Ax);
      break;
    case 'y':
      Serial.println(Ay);
      break;
    case 'z':
      Serial.println(Az);
      break;
    case 'w':
      setLEDs((int)Serial.read());
      break;
    default:
      Serial.println("Not supported");
      break;
   } 
  }
  
}
