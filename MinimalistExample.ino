/******************************************************************************
MinimalistExample.ino

Marshall Taylor @ SparkFun Electronics
May 20, 2015
https://github.com/sparkfun/LSM6DS3_Breakout
https://github.com/sparkfun/SparkFun_LSM6DS3_Arduino_Library

Description:
Most basic example of use.

Example using the LSM6DS3 with basic settings.  This sketch collects Gyro and
Accelerometer data every second, then presents it on the serial monitor.

Resources:
Uses Wire.h for i2c operation
Uses SPI.h for SPI operation
Either can be omitted if not used

Development environment specifics:
Arduino IDE 1.6.4
Teensy loader 1.23

Hardware connections:
Connect I2C SDA line to A4
Connect I2C SCL line to A5
Connect GND and 3.3v power to the IMU

This code is released under the [MIT License](http://opensource.org/licenses/MIT).

Please review the LICENSE.md file included with this example. If you have any questions 
or concerns with licensing, please contact techsupport@sparkfun.com.

Distributed as-is; no warranty is given.
******************************************************************************/

#include "SparkFunLSM6DS3.h"
#include "Wire.h"
#include "SPI.h"

//neopixel
#include <Adafruit_NeoPixel.h>
#define PIN 33
#define NUM_LEDS 18
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

LSM6DS3 myIMU(I2C_MODE, 0x6A); //Default constructor is I2C, addr 0x6B

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(1000); //relax...
  Serial.println("Processor came out of reset.\n");
  
  //Call .begin() to configure the IMU
  myIMU.begin();  
  //central gem
  pinMode(32, OUTPUT);
  
  //led strip
  strip.begin();
  strip.show();

  // test led
  pinMode(13, OUTPUT);
}


void loop()
{
  // neopixel strip
  CylonBounce(0, 0, 0xff, 1, 400, 50);
  
  //Get all parameters
  //Serial.print("\nAccelerometer:\n");
  //Serial.print(" X = ");
  //Serial.println(myIMU.readFloatAccelX(), 4);
  //Serial.print(" Y = ");
  //Serial.println(myIMU.readFloatAccelY(), 4);
  //Serial.print(" Z = ");
//  Serial.println(myIMU.readFloatAccelZ(), 4);

  int orientation;
  digitalWrite(12, HIGH);

  //Serial.print("\nGyroscope:\n");
  //Serial.print(" X = ");
  //Serial.println(myIMU.readFloatGyroX(), 4);
  //Serial.print(" Y = ");
  //Serial.println(myIMU.readFloatGyroY(), 4);
  //Serial.print(" Z = ");
  //Serial.println(myIMU.readFloatGyroZ(), 4);

  //int gyroZ = myIMU.readFloatGyroZ();
  //int gyroY = myIMU.readFloatGyroY();
  //int gyroX = myIMU.readFloatGyroX();

  // Simple integer assignment
  //if (orientation = 0) {Serial.println("default mode");}
  //if (orientation = 1) {Serial.println("vertical");}
  //if (orientation = 2) {Serial.println("horizontal");}
  

  if (myIMU.readFloatAccelX() > .8){
    orientation = 1;
    //digitalWrite(22, LOW); // Turns on an LED if value is over 500
    digitalWrite(13, LOW);
    Serial.println("vertical");
  }
  else {
    orientation = 2;
    //digitalWrite(22, HIGH);
    digitalWrite(13, HIGH);
    Serial.println("horizontal");
  }
  delay(50);
}

//neopixel logic
void showStrip() {
   strip.show();
}

void setPixel(int Pixel, byte red, byte green, byte blue) {
   strip.setPixelColor(Pixel, strip.Color(red, green, blue));
}

void setAll(byte red, byte green, byte blue) {
  for(int i = 0; i < NUM_LEDS; i++ ) {
    setPixel(i, red, green, blue);
  }
  showStrip();
}

void CylonBounce(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay){

  for(int i = 0; i < NUM_LEDS-EyeSize-2; i++) {
    setAll(0,0,0);
    setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red, green, blue);
    }
    setPixel(i+EyeSize+1, red/10, green/10, blue/10);
    showStrip();
    delay(SpeedDelay);
  }

  delay(ReturnDelay);

  for(int i = NUM_LEDS-EyeSize-2; i > 0; i--) {
    setAll(0,0,0);
    setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red, green, blue);
    }
    setPixel(i+EyeSize+1, red/10, green/10, blue/10);
    showStrip();
    delay(SpeedDelay);
  }
 
  delay(ReturnDelay);
}
