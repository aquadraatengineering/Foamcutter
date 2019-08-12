#include "ToggleButton.h"
#include "AssetsCache.h"

using namespace std;
using namespace ci;
using namespace ci::app;


ToggleButtonRef ToggleButton::create()
{
	ToggleButtonRef ref = std::make_shared<ToggleButton>();

	return ref;
}

ToggleButton::ToggleButton()
{

}


void ToggleButton::setup(std::string imagePathOn, std::string imagePathOff)
{
	mImageOn = po::scene::ImageView::create(CACHE()->getTexture(imagePathOn));
	addSubview(mImageOn);


	mImageOff = po::scene::ImageView::create(CACHE()->getTexture(imagePathOff));
	addSubview(mImageOff);
	setState(true);
}
void ToggleButton::setState(bool on) 
{
	if (on) 
	{
		mImageOn->setVisible(true);
		mImageOff->setVisible(false);
	}
	else
	{
		mImageOn->setVisible(false);
		mImageOff->setVisible(true);
	}
	state = on;

}
void ToggleButton::mouseDown(po::scene::MouseEvent& event)
{
	mSignalPressed.emit();

}