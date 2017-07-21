#ifndef __IV_AIR_H_
#define __IV_AIR_H_

#include <IRremote.h>
#include "Common.h"

#define SEND_FREQ 38	// kHz

/* The Raw Code of Opening or Closing The Air-conditioner */
unsigned int openAirCode[]={
8950,4400,650,1650,650,600,600,550,650,550,
600,1650,650,600,600,600,600,550,600,600,
600,600,600,600,600,1600,650,600,600,600,
600,600,600,600,600,600,600,550,650,550,
600,600,600,600,600,600,600,600,600,550,
650,550,600,600,600,600,600,600,600,1600,
650,600,600,1650,650,600,600,550,650,1600,
650,600,600
};
unsigned int closeAirCode[]={
8950,4400,650,1650,650,600,600,550,650,550,
600,1650,650,600,600,600,600,550,600,600,
600,600,600,600,600,1600,650,600,600,600,
600,600,600,600,600,600,600,550,650,550,
600,600,600,600,600,600,600,600,600,550,
650,550,600,600,600,600,600,600,600,1600,
650,600,600,1650,650,600,600,550,650,1600,
650,600,600
};

void OpenTheAir(IRsend &irsend)
{
  irsend.sendRaw(openAirCode,sizeof(openAirCode)/sizeof(unsigned int),SEND_FREQ);
}
void CloseTheAir(IRsend &irsend)
{
  irsend.sendRaw(closeAirCode,sizeof(closeAirCode)/sizeof(unsigned int),SEND_FREQ);
}

#endif