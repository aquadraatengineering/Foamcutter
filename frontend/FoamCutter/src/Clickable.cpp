#include "Clickable.h"
#include "FocusManager.h"
using namespace std;
using namespace ci;
using namespace ci::app;


Clickable::Clickable()
{
	setupClickable();
}




void Clickable::setupClickable(){

	

	// Add event listeners
	mConnections += getSignal(po::scene::MouseEvent::DOWN_INSIDE).connect(std::bind(&Clickable::_mouseDownInside, this, std::placeholders::_1));

	mConnections += getSignal(po::scene::MouseEvent::UP).connect(std::bind(&Clickable::_mouseUp, this, std::placeholders::_1));
	mConnections += getSignal(po::scene::MouseEvent::DRAG).connect(std::bind(&Clickable::_mouseDrag, this, std::placeholders::_1));

}

void Clickable::_mouseDownInside(po::scene::MouseEvent& event)
{
	event.setPropagationEnabled(mPropagationEnabled);

	if (mEventId == -1) {
		mEventId = 0;
	}

	FOCUS()->setFocus(this);
	mouseDown( event);

}
void Clickable::_mouseDrag(po::scene::MouseEvent& event)
{
	if (mEventId == 0) {
		event.setPropagationEnabled(mPropagationEnabled);
		mouseDrag(event);
		
	}
}

void Clickable::_mouseUp(po::scene::MouseEvent& event)
{
	if (mEventId == 0) {
		event.setPropagationEnabled(mPropagationEnabled);
		mouseUp(event);
		mEventId = -1;
	}
}
void Clickable::mouseDown(po::scene::MouseEvent& event)
{

	
	


}
void Clickable::mouseUp(po::scene::MouseEvent& event)
{
	
}
void Clickable::mouseDrag(po::scene::MouseEvent& event)
{

}

void  Clickable::_setFocus(bool fo) 
{
	hasFocus = fo;
	setFocus(fo);
}
