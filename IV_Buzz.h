#ifndef __IV_BUZZ_H_
#define __IV_BUZZ_H_

#include "Common.h"

#define BUZZ_PIN  4    // BUZZ's PORT

void BuzzInit()
{
  pinMode(BUZZ_PIN,OUTPUT);
  digitalWrite(BUZZ_PIN,HIGH);
}
void BuzzSound(u8 state)
{
  u8 i;
  if(state == 1)
  {
    digitalWrite(BUZZ_PIN,LOW);
    delay(300);
    digitalWrite(BUZZ_PIN,HIGH);
    delay(50);
  }else if(state == 2)
  {
    for(i=0;i<2;i++)
    {
      digitalWrite(BUZZ_PIN,LOW);
      delay(150);
      digitalWrite(BUZZ_PIN,HIGH);
      delay(10);
    }
  }else if(state == 3)
  {
    for(i=0;i<3;i++)
    {
      digitalWrite(BUZZ_PIN,LOW);
      delay(150);
      digitalWrite(BUZZ_PIN,HIGH);
      delay(10);
    }
  }
}
#endif