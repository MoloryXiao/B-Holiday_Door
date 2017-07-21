#include <IRremote.h>
#define RECV_PIN 4
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {
  Serial.begin(9600); 
  irrecv.enableIRIn();
}

void loop() {
  if(irrecv.decode(&results))
  {
    dump(&results);
    irrecv.resume();
  }
}

void dump(decode_results *results)
{
  int count = results->rawlen;
  Serial.print("Raw(");
  Serial.print(count);
  Serial.print("):");
  for(int i=0;i<count;i++)
  {
    Serial.print(results->rawbuf[i]*USECPERTICK);
    Serial.print(",");
    if(i%10==0) Serial.println();
  }
  Serial.println();
}
