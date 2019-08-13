//
//  SerialHandler.cpp
//  Controler
//
//  Created by Kris Temmerman on 11/06/2019.
//

#include "SerialHandler.hpp"
#include "Log.hpp"
#include "GlobalSettings.h"
using namespace ci;
using namespace ci::app;
using namespace std;

void SerialHandler::setup(){
// print the devices
    string name;
	console() << "Devices: " << endl;
    for( const auto &dev : Serial::getDevices() )
        console() << "Device: " << dev.getName() << endl;

    try {
		Serial::Device dev = Serial::Device("COM3");

        name = dev.getName();
        
        mSerial = Serial::create( dev, 115200 );
    }
    catch( SerialExc &exc ) {
        string error = "coult not init serial dev "+name ;
        error+=exc.what();
        LOG()->logError( error );
        return;
    }
   std::this_thread::sleep_for (std::chrono::seconds(1));

    LOG()->log("Serial Connected: " + name);

    updateSettings();
}
void SerialHandler::update()
{
    
    if(mSerial ){
        while( mSerial->getNumBytesAvailable()>2){
            try{
                // read until newline, to a maximum of BUFSIZE bytes
                string mLastString = mSerial->readStringUntil( '\n',80 );
              
                parseString(mLastString);
           
               
            }
            catch( SerialTimeoutExc &exc ) {
              
            }
        }
    }
   
}
void SerialHandler::updateSettings()
{
     LOG()->log("send Settings to controler");
    if(mSerial ){
        string m ="A"+ to_string(GS()->maxAccel.value())+"e";
        mSerial->writeString(m);
        
        string m2 ="M"+ to_string(GS()->fastSpeed.value())+"e";
        mSerial->writeString(m2);
        
        string m3 ="P"+ to_string(GS()->controllerP.value())+"e";
        mSerial->writeString(m3);
    }
    
    
    
}
void SerialHandler::setTargetPos(int pos)
{
      targetState =1;
    string s ="set target: " + to_string(pos);
    LOG()->log(s);
    if(mSerial ){
        string m ="T"+ to_string(pos)+"e";
        mSerial->writeString(m);
    }
    
    
}
void SerialHandler::setSpeed(float speed)
{
      targetState =0;
    string s ="set speed: " + to_string((int)speed)+ "rpm";
    LOG()->log(s);
     if(mSerial ){
         string m ="S"+ to_string((int)speed)+"e";
         mSerial->writeString(m);
     }
    
    
}
void SerialHandler::parseString(std::string input)
{
    if(input.at(0)=='L')
    {
        input.erase(0, 2);
        console()<<"L"<<input<<endl;
        LOG()->log(input);
        
    } else if(input.at(0)=='E')
    {
        input.erase(0, 2);
        console()<<"E"<<input<<endl;
        LOG()->logError(input);
    }
    else if(input.at(0)=='M')
    {
        input.erase(0, 2);
        
        currentPosition =stof(input);
        positionIsDirty =true;
        
    }   else if(input.at(0)=='T')
    {
       
        targetState =2;
    }
    
}
