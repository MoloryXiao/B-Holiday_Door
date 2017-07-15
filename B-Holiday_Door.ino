#include <Servo.h>
#include <SPI.h>
#include <RFID.h>
#include <SoftwareSerial.h>
#define u8 unsigned char

#define SERVO_PIN 7    //Servo's PORT
#define BUZZ_PIN  4
#define ID_HEX_NUM 5
#define NOTE_DL1 147

#define OPEN_VALUE 90
#define TEST_VALUE 1
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
typedef struct
{
  u8 serNum[ID_HEX_NUM];
}ID_CARD;

/* Access-Cards's Definition */
ID_CARD cardsSet[3]=
{
  {0xEF,0x99,0xD2,0x77,0xD3},   // my school-card
  {0xAF,0x89,0x75,0x71,0x22},    // my bank-card
  {0xCF,0xF1,0xEA,0x77,0xA3}
};

Servo myservo;        //Create A Servo Object
RFID rfid(10,9);      //D10--RC522's SDA、D5--rc522's RST
SoftwareSerial serial2(3,2);

void PrintCardNum(RFID &rfid)
{
  u8 i;
  for(i=0;i<ID_HEX_NUM;i++)
  {
    Serial.print(rfid.serNum[i],HEX); Serial.print(" ");
  }
  Serial.println();
}

bool VerifyIdentity(RFID &rfid)
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
      return true;
  }
  return false;
}
void buzz(u8 state)
{
  if(state)
  {
    digitalWrite(4,LOW);
    delay(300);
    digitalWrite(4,HIGH);
    delay(50);
  }else
  {
    digitalWrite(4,LOW);
    delay(150);
    digitalWrite(4,HIGH);
    delay(10);
    digitalWrite(4,LOW);
    delay(150);
    digitalWrite(4,HIGH);
    delay(50);
  }
  
}
void OpenTheDoor()
{
  buzz(1);
  myservo.write(OPEN_VALUE);
  delay(3000);
  myservo.write(0);
}
void KeepClose()
{
  buzz(0);
}
void setup() {
  Serial.begin(9600); 
  serial2.begin(9600);
  myservo.attach(SERVO_PIN);    //connect to servo
  myservo.write(0);
  SPI.begin();
  rfid.init();

  pinMode(BUZZ_PIN,OUTPUT);digitalWrite(BUZZ_PIN,HIGH);
}
void debug()
{
  u8 serialRead;
  if(serial2.available())
  {
    serialRead=serial2.read();
    if(serialRead==56)
    {
      OpenTheDoor();
      rfid.init();
      SPI.begin();
    }
    Serial.println("Reset OK!");
  }
}
void debug2()
{
  u8 serialRead;
  if(Serial.available())
  {
    serialRead=Serial.read();
    if(serialRead==56)
    {
      delay(2000);
      OpenTheDoor();
    }
  }
}
void loop() {
  // Search Cards Constantly
  if (rfid.isCard()) {
    Serial.println("Find the card!");
    // Read the card's ID-Code
    if (rfid.readCardSerial()) {
      u8 identityState;
      Serial.print("The card's number is : ");
      PrintCardNum(rfid);
      identityState=VerifyIdentity(rfid);
      if(identityState) 
      {
        Serial.println("Yes ! Access to Enter!");
        //buzz(1);
        OpenTheDoor();
      }
      else
      {
        Serial.println("NO ! This Card Was Undefined!");
        KeepClose();
      }
    }
    // Select it, Avoid to Read this Card Repeatedly
    // The Return Value is Card's Capacity
    rfid.selectTag(rfid.serNum);
  }
  //rfid.halt();
  debug();
  debug2();
}
