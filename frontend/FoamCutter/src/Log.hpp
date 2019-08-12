//
//  Log.hpp
//  Controler
//
//  Created by Kris Temmerman on 11/06/2019.
//

#pragma once
#include "cinder/app/App.h"
#include "Singleton.h"
#include "cinder/Serial.h"
class Log
{
    
public:
    Log(){}
   
    void setup();
    void logError(std::string error);
    void log(std::string log);
   
    std::vector<std::pair<std::string,int>> logData;
    
    
    bool logDirty=false;
};
typedef Singleton<Log> LogSingleton;

inline Log* LOG(){
    return LogSingleton::Instance();
}
