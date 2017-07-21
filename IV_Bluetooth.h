#ifndef __IV_BLUETOOTH_H_
#define __IV_BLUETOOTH_H_

#include <SoftwareSerial.h>
#include "Common.h"
#include "IV_Door.h"
#include "IV_Air.h"
#include "IV_Buzz.h"

void BT_Scanner(SoftwareSerial &serial2,Servo &myservo,IRsend &irsend)
{
  u8 serialRead;
  if(serial2.available())
  {
    serialRead=serial2.read();
    if(serialRead==56)  // read '8'
    {
      OpenTheDoor(myservo);
      Serial.println("Open the Door and Reset Successfully!");
      BuzzSound(2);
    }
    if(serialRead==55)  // read '7'
    {
      OpenTheAir(irsend);
      Serial.println("OK ! Open the Air-conditioner!");
      BuzzSound(1);
    }
    if(serialRead==57)  // read '9'
    {
      CloseTheAir(irsend);
      Serial.println("OK ! Close the Air-conditioner!");
      BuzzSound(1);
    }
  }
}
void debug(Servo &myservo)
{
  u8 serialRead;
  if(Serial.available())
  {
    serialRead=Serial.read();
    if(serialRead==56)
    {
      delay(2000);
      OpenTheDoor(myservo);
    }
  }
}
#endif