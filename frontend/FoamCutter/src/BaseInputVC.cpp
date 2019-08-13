#include "BaseInputVC.h"

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
	getView()->addSubview(stopBtn);



	homeBtn = ImageButton::create();
	homeBtn->setup("ui/bottom.png", 0);
	homeBtn->setPosition(120, 0);
	getView()->addSubview(homeBtn);
	//homeBtn->mSignalPressed.connect(std::bind(&ManualInputVC::setTextInput, this));

	
	//homeBtn->mSignalPressed.connect(std::bind(&ManualInputVC::setTextInput, this));
	float posX  =480;
	float posY = 0;
	upFastBtn = ImageButton::create();
	upFastBtn->setup("ui/fastbtn.png", 0);
	upFastBtn->setPosition(posX, posY);
	getView()->addSubview(upFastBtn);

	posY += 120;
	upBtn = ImageButton::create();
	upBtn->setup("ui/slowbtn.png", 0);
	upBtn->setPosition(posX, posY);
	getView()->addSubview(upBtn);


	posY += 120+100;
	posX += 100;

	downBtn = ImageButton::create();
	downBtn->setup("ui/slowbtn.png", 3.1415);
	downBtn->setPosition(posX, posY);
	getView()->addSubview(downBtn);


	posY += 120;
	downFastBtn = ImageButton::create();
	downFastBtn->setup("ui/fastbtn.png", 3.1415);
	downFastBtn->setPosition(posX, posY);
	getView()->addSubview(downFastBtn);

}