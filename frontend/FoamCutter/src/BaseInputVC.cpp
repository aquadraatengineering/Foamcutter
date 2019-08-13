#include "BaseInputVC.h"
#include "SerialHandler.hpp"
#include "GlobalSettings.h"
using namespace po::scene;

using namespace ci;
using namespace ci::app;
using namespace std;


BaseInputVCRef  BaseInputVC::create()
{
	BaseInputVCRef ref = std::make_shared< BaseInputVC>();

	return ref;
}


void  BaseInputVC::setup() {

	ShapeViewRef mShape = po::scene::ShapeView::createRoundedRect(620, 800, 8);
	mShape->setFillColor(Color::gray(0.9));
	mShape->setPosition(-20, -20);
	getView()->addSubview(mShape);


	stopBtn = ImageButton::create();
	stopBtn->setup("ui/stopBtn.png", 0);
	stopBtn->setPosition(0, 0);
	stopBtn->mSignalPressed.connect([](void) {SERIAL()->setSpeed(0); });
	getView()->addSubview(stopBtn);




	//homeBtn->mSignalPressed.connect(std::bind(&ManualInputVC::setTextInput, this));

	
	//homeBtn->mSignalPressed.connect(std::bind(&ManualInputVC::setTextInput, this));
	float posX  =480;
	float posY = 0;
	upFastBtn = ImageButton::create();
	upFastBtn->setup("ui/fastbtn.png", 0);
	upFastBtn->setPosition(posX, posY);
	upFastBtn->mSignalPressed.connect([](void) {SERIAL()->setSpeed(GS()->fastSpeed.value()); });
	upFastBtn->mSignalReleased.connect([](void) {SERIAL()->setSpeed(0); });
	getView()->addSubview(upFastBtn);

	posY += 120;
	upBtn = ImageButton::create();
	upBtn->setup("ui/slowbtn.png", 0);
	upBtn->setPosition(posX, posY);
	upBtn->mSignalPressed.connect([](void) {SERIAL()->setSpeed(GS()->slowSpeed.value()); });
	upBtn->mSignalReleased.connect([](void) {SERIAL()->setSpeed(0); });
	getView()->addSubview(upBtn);


	posY += 120+100;
	posX += 100;

	downBtn = ImageButton::create();
	downBtn->setup("ui/slowbtn.png", 3.1415);
	downBtn->setPosition(posX, posY);
	downBtn->mSignalPressed.connect([](void) {SERIAL()->setSpeed(-GS()->slowSpeed.value()); });
	downBtn->mSignalReleased.connect([](void) {SERIAL()->setSpeed(0); });
	getView()->addSubview(downBtn);


	posY += 120;
	downFastBtn = ImageButton::create();
	downFastBtn->setup("ui/fastbtn.png", 3.1415);
	downFastBtn->setPosition(posX, posY);
	downFastBtn->mSignalPressed.connect([](void) {SERIAL()->setSpeed(-GS()->fastSpeed.value()); });
	downFastBtn->mSignalReleased.connect([](void) {SERIAL()->setSpeed(0); });
	getView()->addSubview(downFastBtn);


	homeBtn = ImageButton::create();
	homeBtn->setup("ui/bottom.png", 0);
	homeBtn->setPosition(480, 120*4);
	homeBtn->mSignalPressed.connect([](void) {SERIAL()->setSpeed(-GS()->fastSpeed.value()); });

	getView()->addSubview(homeBtn);

	/*
	SERIAL()->setSpeed(GS()->fastSpeed.value());
 SERIAL()->setSpeed(0);
	else  if (type == 1)
	{
		SERIAL()->setSpeed(GS()->slowSpeed.value());
	}
	else if (type == 2)
	{
		SERIAL()->setSpeed(-GS()->slowSpeed.value());
	}
	else if (type == 3)
	{
		SERIAL()->setSpeed(-GS()->fastSpeed.value());*/
}