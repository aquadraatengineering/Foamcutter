#pragma once
#include "Clickable.h"
#include "poScene/ImageView.h"
#include "poScene/ShapeView.h"
#include "poScene/TextView.h"

class  TextInput;
typedef std::shared_ptr<TextInput> TextInputRef;

typedef ci::signals::Signal<void()> pressSignal;


class TextInput : public Clickable {

public:


	static TextInputRef create();
	TextInput();
	void setup(int fontSize,int maxChars,float min, float max);
	void update();
	po::scene::ShapeViewRef mShape;

	virtual void setFocus(bool focus);
	virtual void keyDown(ci::app::KeyEvent event);

	int cursorPos = 0;
	std::string text = "";
	void addAddCursorPos(std::string in, int pos);
	void redrawText();
	po::scene::ImageViewRef textView;

	float mMin;
	float mMax;
	int maxChars;
	int fontSize;
	ci::vec2 charSizeFirst;
	ci::vec2 charSizeNext;
	ci::vec2 textSize;
	ci::vec2 boxSize;
	ci::vec2 margin =ci::vec2(5,5);
	float cursorOffset = 0;

	po::scene::ShapeViewRef cursor;
	void changeCursor();
	double nextCursorSwitchTime = 0.0;

	virtual void mouseDown(po::scene::MouseEvent& event);
	
	void setSelect(int start, int size);
	void stopSelection();

	bool	isSelected = false;
	int selectStart = 0;
	int selectSize = 0;
	po::scene::ShapeViewRef selectShape;
	

	double lastMouseDown = 0;


	pressSignal mSignalPressed;
	bool checkValue();
	float getValue();

	void clear();
};
