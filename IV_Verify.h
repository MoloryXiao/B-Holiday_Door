#ifndef __IV_VERIFY_H_
#define __IV_VERIFY_H_

#include "Common.h"

#define ID_HEX_NUM 5      // The Number of HEX For ID in Card

typedef struct
{
  u8 openDoorFlag;            // The Flag of Opening the Door
  u8 openAirFlag;             // The Flag of Opening the Air
  u8 closeAirFlag;            // The Flag of Closing the Air
  u8 serNum[ID_HEX_NUM];      // ID Code
}ID_CARD;

/* Access-Cards's Definition */
ID_CARD cardsSet[3]=
{
  {1,0,0,{0xEF,0x99,0xD2,0x77,0xD3}},   // my school-card
  {1,0,0,{0xAF,0x89,0x75,0x71,0x22}},   // my bank-card
  {1,0,0,{0xCF,0xF1,0xEA,0x77,0xA3}}    // Hong-Xue-Lin school-card
};

bool VerifyIdentity(RFID &rfid,u8 &loc)
{
  u8 i,j,count;
  u8 cardsNum = sizeof(cardsSet)/sizeof(ID_CARD);   // Get the CardsNum
  for(i=0;i<cardsNum;i++)
  {
    count=0;
    for(j=0;j<ID_HEX_NUM;j++)
      if(cardsSet[i].serNum[j]==rfid.serNum[j])
        count++;
    if(count == ID_HEX_NUM)   // Every Hex is Correct
    {
      loc = i;
      return true;
    }
  }
  return false;
}
bool VerifyDoorFlag(u8 cardLocInSet)
{
  if(cardsSet[cardLocInSet].openDoorFlag) return true;
  else return false;
}
bool VerifyAirOpenFlag(u8 cardLocInSet)
{
  if(cardsSet[cardLocInSet].openAirFlag) return true;
  else return false;
}
bool VerifyAirCloseFlag(u8 cardLocInSet)
{
  if(cardsSet[cardLocInSet].closeAirFlag) return true;
  else return false;
}
#endif