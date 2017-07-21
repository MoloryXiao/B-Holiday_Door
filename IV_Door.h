#ifndef __IV_DOOR_H_
#define __IV_DOOR_H_

#include <Servo.h>
#include "Common.h"

#define SERVO_PIN 7    // Servo's PORT

#define OPEN_DEGREE 90    // Open The Door of Degree
#define CLOSE_DEGREE 0    // Close The Door of Degree
#define OPEN_DOOR_TIME 3  // The Time of Servo Working on Open_Degree (second)

void OpenTheDoor(Servo &myservo)
{
  //BuzzSound(2);
  myservo.write(OPEN_DEGREE);
  delay(OPEN_DOOR_TIME*1000);
  myservo.write(CLOSE_DEGREE);
}
#endif