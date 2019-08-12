#include "FocusManager.h"
using namespace std;
using namespace ci;
using namespace ci::app;
void FocusManager::setFocus(Clickable * click) 
{
	if (currentFocus == click) return;
	if (currentFocus) 
	{
		currentFocus->_setFocus(false);
	}
	currentFocus = click;
	if (currentFocus) {
		currentFocus->_setFocus(true);
	}
}
void FocusManager::clearFocus() 
{
	setFocus(nullptr);

}
void FocusManager::keyDown(ci::app::KeyEvent event) 
{
	if (currentFocus)
	{
		currentFocus->keyDown(event);
	}
}