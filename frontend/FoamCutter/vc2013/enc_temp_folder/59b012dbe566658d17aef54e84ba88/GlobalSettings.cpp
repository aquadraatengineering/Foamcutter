

#include "GlobalSettings.h"
#include "cinder/Utilities.h"

using namespace std;
using namespace ci;



GlobalSettings::GlobalSettings(){


}


void GlobalSettings::setup(std::string appName){

	mSettingManager.setAppName(appName);
	mSettingManager.readSettings();

	// debug mode on or off
	debugMode = Setting<bool>("showSettings", true);
	mSettingManager.addSetting(&debugMode);
 

    

    slowSpeed= Setting<float>("slowSpeed",1.0) .setSteps(1.f);
    mSettingManager.addSetting(&slowSpeed);
    
	fastSpeed= Setting<float>("fastSpeed",10.0) .setSteps(10.f);
    mSettingManager.addSetting(&fastSpeed);
    
     maxAccel= Setting<float>("maxAxel",400.0) .setSteps(1.f);
    mSettingManager.addSetting(&maxAccel);
    
    
    heightOffset = Setting<float>("heightOffset",0.0) .setSteps(0.1f);
    mSettingManager.addSetting(&heightOffset);
  
    minDist= Setting<float>("minDist",84.0) .setSteps(1.f);
    mSettingManager.addSetting(&minDist);
    
    minDistInput= Setting<float>("minDistInput",630.0) .setSteps(1.f);
    mSettingManager.addSetting(&minDistInput);
    
    maxDist= Setting<float>("maxDist",600.0) .setSteps(1.f);
    mSettingManager.addSetting(&maxDist);
    
    maxDistInput= Setting<float>("maxDistInput",3610.0) .setSteps(1.f);
    mSettingManager.addSetting(&maxDistInput);
    
    controllerP= Setting<float>("controllerP",1.0) .setSteps(0.5f);
    mSettingManager.addSetting(&controllerP);
}








