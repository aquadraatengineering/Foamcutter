//
//  SerialHandler.hpp
//  Controler
//
//  Created by Kris Temmerman on 11/06/2019.
//

#pragma once
#include "cinder/app/App.h"
#include "Singleton.h"
#include "cinder/Serial.h"
class SerialHandler
{
    
public:
    SerialHandler(){}
    ci::SerialRef    mSerial;
    void setup();
    void update();
    void parseString(std::string input);
    void setSpeed(float speed);
    void setTargetPos(int pos);
    void updateSettings();
    float currentPosition= -1;
    bool positionIsDirty =false;
    int targetState =0;
};
typedef Singleton<SerialHandler> SerialHandlerSingleton;

inline SerialHandler* SERIAL(){
    return SerialHandlerSingleton::Instance();
}
