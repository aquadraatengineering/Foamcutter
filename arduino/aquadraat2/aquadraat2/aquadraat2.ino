

#include "Motor.h"


Motor motor;


unsigned long previousTime = 0;

int sensorReadTime =0;

float currentPos;
float targetPos = 0;
float targetReached = true;
float targetSearch = false;

float p = 100;

void setup() {

  Serial.begin(115200);

  while (! Serial) {
    delay(1);
  }



  motor.setup();


analogReadResolution(12);
  previousTime = micros();
}

void loop() {

  unsigned long currentTime = micros();
  int delta = currentTime - previousTime;
  previousTime = currentTime;

  motor.update(delta);

  getInputData();
  getSensorData(delta);

  if (targetSearch && !targetReached )
  {
    float error =  currentPos-targetPos;
    if (abs(error) < 1)
    {
      targetReached = true;
      motor.setSpeed(0);
      Serial.print("T ");
        Serial.println();
    } else
    {
      motor.setSpeed(error * p);
    }

  }



}
void getInputData()
{
  if (Serial.available() > 2 )
  {
    String message = Serial.readStringUntil('e');
    if (message.startsWith("S"))
    {
      message.remove(0, 1);
      float motorTargetSpeed = message.toFloat();
      motor.setSpeed(motorTargetSpeed);
      targetSearch  = false;
    }
    else if (message.startsWith("A"))
    {
      message.remove(0, 1);
      motor.maxAcc = message.toFloat();
    }else if (message.startsWith("P"))
    {
      message.remove(0, 1);
      p = message.toFloat();
    }
    else if (message.startsWith("M"))
    {
      message.remove(0, 1);
      motor.maxSpeed = message.toFloat();

    }
    else if (message.startsWith("T"))
    {
      message.remove(0, 1);
      targetPos = message.toFloat();
      targetReached = false;
      targetSearch  = true;
    }
  }

}

void getSensorData(int delta)
{
  sensorReadTime +=delta;
  if(sensorReadTime>20000){
        sensorReadTime  =0;
        currentPos =analogRead(A0);
        Serial.print("M ");
        Serial.println(currentPos);
  }

  

}
