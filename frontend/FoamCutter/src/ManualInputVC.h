#pragma once
#pragma once

#include "poScene/ViewController.h"
#include "TextInput.h"
#include "ImageButton.h"
#include "ToggleButton.h"
class ManualInputVC;
typedef std::shared_ptr< ManualInputVC>  ManualInputVCRef;

class  ManualInputVC : public po::scene::ViewController
{
public:
	static  ManualInputVCRef create();
	void setup();
	void setTextInput();
	void setTopBottomInput();
	TextInputRef textInput;
	ImageButtonRef nextBtn;
	ToggleButtonRef topBottomButton;
	bool isTop = true;
};