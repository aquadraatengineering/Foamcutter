#pragma once
#include "Clickable.h"
#include "poScene/ImageView.h"
#include "poScene/ShapeView.h"

class  ToggleButton;
typedef std::shared_ptr<ToggleButton> ToggleButtonRef;

typedef ci::signals::Signal<void()> pressSignal;


class ToggleButton : public Clickable {

public:
	static ToggleButtonRef create();
	ToggleButton();


	void setup(std::string imagepathOn, std::string imagepathOf);
	void setState(bool on);
	bool state = true;
	virtual void mouseDown(po::scene::MouseEvent& event);

	po::scene::ImageViewRef mImageOn;
	po::scene::ImageViewRef mImageOff;

	pressSignal mSignalPressed;
};
