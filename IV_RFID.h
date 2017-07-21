#ifndef __IV_RFID_H_
#define __IV_RFID_H_

#include <SPI.h>
#include <RFID.h>
#include "Common.h"
#include "IV_Air.h"
#include "IV_Door.h"
#include "IV_Buzz.h"
#include "IV_Verify.h"

// The Infrared-Send's PORT is Defined as 3
/* RC522
 *  白 黑 紫 棕 黄 橙 红
  SDA   D10
  SCK   D13
  MOSI  D11
  MISO  D12
  IRQ
  GND   GND
  RST   D9
  3.3V  VCC
*/
void PrintCardNum(RFID &rfid)
{
  u8 i;
  for(i=0;i<ID_HEX_NUM;i++)
  {
    Serial.print(rfid.serNum[i],HEX); Serial.print(",");
  }
  Serial.println();
}

void RFID_Scanner(RFID &rfid,Servo &myservo,IRsend &irsend)
{
  if (rfid.isCard())  // Search Cards Constantly
  {
    Serial.println("Find the card!");
    // Read the Card's ID-Code
    if (rfid.readCardSerial())
    {
      u8 identityState;
      u8 cardLocInSet = -1;

      Serial.print("The Card's Number is : ");
      PrintCardNum(rfid);
      
      identityState = VerifyIdentity(rfid,cardLocInSet);
      if(identityState)
      {
        u8 count=1;
        if(VerifyDoorFlag(cardLocInSet))
        {
          count++;
          Serial.println("Yes ! Access to Enter!");
          OpenTheDoor(myservo);
        }
        if(VerifyAirOpenFlag(cardLocInSet))
        {
          count++;
          OpenTheAir(irsend);
          Serial.println("OK ! Open the Air-conditioner!");
        }
        if(VerifyAirCloseFlag(cardLocInSet))
        {
          count++;
          CloseTheAir(irsend);
          Serial.println("OK ! Close the Air-conditioner!");
        }
        BuzzSound(count);
      }
      else
      {
        Serial.println("NO ! This Card Was Undefined!");
        BuzzSound(1);
      }
    }
    /* Select it, Avoid to Read this Card Repeatedly
       The Return Value is Card's Capacity */
    rfid.selectTag(rfid.serNum);
  }
  //rfid.halt();
}

#endif