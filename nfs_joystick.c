// for playing need for speed

#include "HID-Project.h"
#include<Wire.h>


const int pinAcl = 8;
const int pinSlw = 9;

int buttonState = 0;

const int MPU_addr=0x68;  // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

void setup(){
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);

  pinMode(pinAcl, INPUT_PULLUP);
  pinMode(pinSlw, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);

  Gamepad.begin();

  //debug
  //Serial.begin(9600);
}


void loop(){
  Gamepad.releaseAll();
  
    Wire.beginTransmission(MPU_addr);
    Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
    AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)  
    
    Gamepad.xAxis(AcX);
    //Serial.print("AcX = "); Serial.println(AcX + 0x8000);

    if (digitalRead(pinAcl) == LOW) {
      Gamepad.dPad1(1);
      //Serial.println("+++");
    }
    
    if (digitalRead(pinSlw) == LOW) {
      Gamepad.dPad2(1);
      //Serial.println("---");
    }
  
  Gamepad.write();
}
