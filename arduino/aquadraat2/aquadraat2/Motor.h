#ifndef Motor_h
#define Motor_h

#include <arduino.h>
class Motor
{

  public:
    int enPin = 52;
    int dirPin = 50;
    int stepPin = 48;

    float targetSpeed = 0;
    float currentSpeed = 0;
    float maxAcc =200;
    float maxSpeed =200;
    int currentStepTime = 0;
    int stepTime = 0;
    bool stepPinState = false;
    Motor() {};

    void setup()
    {
      pinMode(dirPin , OUTPUT);
      pinMode(stepPin, OUTPUT);
      pinMode(enPin, OUTPUT);
      digitalWrite(dirPin, LOW);
      digitalWrite(stepPin, LOW);
      digitalWrite(enPin, LOW);


    }
    void setSpeed(float tarSpeed)
    {
      targetSpeed =min( tarSpeed,maxSpeed);
       targetSpeed =max(   targetSpeed,-maxSpeed);
    }

    void update(int delta)
    {


      if (currentSpeed != targetSpeed)
      {
          if(currentSpeed <targetSpeed)
          {
            currentSpeed +=maxAcc*delta/1000000.f;
            if(currentSpeed>targetSpeed)
            {
              currentSpeed=targetSpeed;
            }
          }
          
          if(currentSpeed >targetSpeed)
          {
            currentSpeed -=maxAcc*delta/1000000.f;
            if(currentSpeed<targetSpeed)
            {
              currentSpeed=targetSpeed;
            }
          }
          
          
         
        if ( currentSpeed < 0) {
          digitalWrite(dirPin, LOW);
        } else
        {
          digitalWrite(dirPin, HIGH);
        }
        //200steps/pr *2=400
        if (currentSpeed != 0)
        {
          float pulsPMin =  abs(currentSpeed) * 400;
          float pulsSec =  pulsPMin / 60;

          stepTime = 1000000 / pulsSec;
        }
      }
      if (currentSpeed != 0) {
        currentStepTime += delta;
        if (currentStepTime > stepTime)
        {
          currentStepTime -= stepTime;
          stepPinState = !stepPinState;
          digitalWrite(stepPin, stepPinState);
        }
      }
    }




};
#endif
