#include "Common.h"
#include "IV_Air.h"
#include "IV_Buzz.h"
#include "IV_Door.h"
#include "IV_RFID.h"
#include "IV_Verify.h"
#include "IV_Bluetooth.h"

/* 作一个修改 将蓝牙串口从3和2移至6和5 把3腾出来给红外模块
   红外模块就连在3的位置 电源从那边取 */

IRsend irsend;                // Create a RedOutSend Object
Servo myservo;                // Create a Servo Object
RFID rfid(10,9);              // D10--RC522's SDA、D5--rc522's RST
SoftwareSerial serial2(6,5);

void setup() {
  Serial.begin(9600); 
  serial2.begin(9600);

  myservo.attach(SERVO_PIN);    //Connect To Servo
  myservo.write(CLOSE_DEGREE);

  SPI.begin();
  rfid.init();

  BuzzInit();
}
void loop() {
  RFID_Scanner(rfid,myservo,irsend);
  BT_Scanner(serial2,myservo,irsend);
}
