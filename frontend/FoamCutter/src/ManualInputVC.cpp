#include "ManualInputVC.h"
#include "FocusManager.h"
#include "LogView.hpp"
#include "AssetsCache.h"
using namespace po::scene;

using namespace ci;
using namespace ci::app;
using namespace std;


 ManualInputVCRef  ManualInputVC::create()
{
	 ManualInputVCRef ref = std::make_shared< ManualInputVC>();

	return ref;
}


void  ManualInputVC::setup() {

	ShapeViewRef mShape = po::scene::ShapeView::createRoundedRect(600,140, 8);
	mShape->setFillColor(Color::gray(0.9));
	mShape->setPosition(-20, -20);
	getView()->addSubview(mShape);


	textInput = TextInput::create();
	textInput->setup(75, 8,0,250);
	textInput->setPosition(120, 2);
	getView()->addSubview(textInput);




	nextBtn = ImageButton::create();
	nextBtn->setup("ui/nextBtn.png", 0);
	nextBtn->setPosition(480, 0);
	getView()->addSubview(nextBtn);

	nextBtn->mSignalPressed.connect(std::bind(& ManualInputVC::setTextInput, this));
	textInput->mSignalPressed.connect(std::bind(& ManualInputVC::setTextInput, this));

	


	topBottomButton = ToggleButton::create();
	topBottomButton->setup("ui/topcutter.png", "ui/bottomcutter.png");
	topBottomButton->mSignalPressed.connect(std::bind(&ManualInputVC::setTopBottomInput, this));
	topBottomButton->setPosition(0, 0);
	getView()->addSubview(topBottomButton);

}
void  ManualInputVC::setTopBottomInput()
{

	isTop = !isTop;
	topBottomButton->setState(isTop);

}
void  ManualInputVC::setTextInput()
{
	if (textInput->checkValue())
	{
		float input = textInput->getValue();
		//SERIAL()->setTargetPos();


		textInput->clear();
		FOCUS()->clearFocus();
		isTop = !isTop;
		topBottomButton->setState(isTop);
	}
}


