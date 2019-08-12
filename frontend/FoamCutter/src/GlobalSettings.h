#pragma once
#include "cinder/app/App.h"

#include "Singleton.h"

#include "SettingManager.h"

#include "SettingBase.h"
#include "SettingString.h"

class GlobalSettings{


public:

	GlobalSettings();
	void setup(std::string appName);
	


    SettingManager mSettingManager;


  
    
	Setting<bool>   debugMode;
	
    Setting<float> heightOffset;
    Setting<float> slowSpeed;
    Setting<float> fastSpeed;
    Setting<float> maxAccel;
    
    Setting<float> minDist;
    Setting<float> minDistInput;
    Setting<float> maxDist;
    Setting<float> maxDistInput;
    
    Setting<float> controllerP;
};


typedef Singleton<GlobalSettings> GlobalSettingsSingleton;

inline GlobalSettings* GS(){
	return GlobalSettingsSingleton::Instance();
}

