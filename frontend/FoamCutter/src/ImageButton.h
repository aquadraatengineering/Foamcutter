#pragma once
#include "Clickable.h"
#include "poScene/ImageView.h"
#include "poScene/ShapeView.h"

class  ImageButton;
typedef std::shared_ptr<ImageButton> ImageButtonRef;

typedef ci::signals::Signal<void()> pressSignal;


class ImageButton : public Clickable {

public:
	static ImageButtonRef create();
	ImageButton();
	
	
	void setup(std::string imagepath, float rotation=0);
	virtual void mouseDown(po::scene::MouseEvent& event);
	virtual void mouseUp(po::scene::MouseEvent& event);
	po::scene::ImageViewRef mImage;

	pressSignal mSignalReleased;
	pressSignal mSignalPressed;
};
