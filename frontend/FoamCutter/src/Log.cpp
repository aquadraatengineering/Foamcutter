//
//  Log.cpp
//  Controler
//
//  Created by Kris Temmerman on 11/06/2019.
//

#include "Log.hpp"
using namespace std;
void Log::setup()
{
    
    
}
void Log::logError(string error)
{
    logData.push_back(pair<string,int>(error,1));
     logDirty =true;
    
  
}
void Log::log(std::string log)
{
    logData.push_back(pair<string,int>(log,0));
    logDirty =true;
    
    
    
}

