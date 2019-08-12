#pragma once
#include "cinder/app/App.h"
#include "Singleton.h"
#include "Clickable.h"
class FocusManager
{

public:
	FocusManager() {};
	void setFocus(Clickable * click);
	void clearFocus();
	Clickable * currentFocus =nullptr;
	void keyDown(ci::app::KeyEvent event);
};
typedef Singleton<FocusManager> FocusManagerSingleton;

inline FocusManager* FOCUS() {
	return FocusManagerSingleton::Instance();
}
