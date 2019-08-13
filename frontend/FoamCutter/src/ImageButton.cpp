#include "ImageButton.h"
#include "AssetsCache.h"

using namespace std;
using namespace ci;
using namespace ci::app;


ImageButtonRef ImageButton::create()
{
	ImageButtonRef ref = std::make_shared<ImageButton>();

	return ref;
}

ImageButton::ImageButton()
{

}


void ImageButton::setup(std::string imagePath, float rotation)
{
	mImage = po::scene::ImageView::create(CACHE()->getTexture(imagePath));
	//mImage->setAlignment(po::scene::Alignment::CENTER_CENTER);
	mImage->setRotation(rotation);
	vec2 size = mImage->getSize();


	addSubview(mImage);
}

void ImageButton::mouseDown(po::scene::MouseEvent& event) 
{
	mSignalPressed.emit();
	setAlpha(0.9);

}
void ImageButton::mouseUp(po::scene::MouseEvent& event)
{
	setAlpha(1.0);

}