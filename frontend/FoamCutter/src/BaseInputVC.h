#pragma once


#include "poScene/ViewController.h"
#include "TextInput.h"
#include "ImageButton.h"
#include "ToggleButton.h"
class BaseInputVC;
typedef std::shared_ptr< BaseInputVC>  BaseInputVCRef;

class  BaseInputVC : public po::scene::ViewController
{
public:
	static  BaseInputVCRef create();
	void setup();
	
	ImageButtonRef homeBtn;
	ImageButtonRef stopBtn;

	ImageButtonRef upFastBtn;
	ImageButtonRef upBtn;
	ImageButtonRef downBtn;
	ImageButtonRef downFastBtn;

};