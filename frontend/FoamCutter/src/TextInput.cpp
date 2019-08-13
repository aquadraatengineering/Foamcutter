#include "TextInput.h"
#include "AssetsCache.h"

using namespace std;
using namespace ci;
using namespace ci::app;


TextInputRef TextInput::create()
{
	TextInputRef ref=std::make_shared<TextInput>();

	return ref;
}

TextInput::TextInput()
{

}


void TextInput::setup(int _fontSize, int _maxChars,float min, float max)
{
	mMin = min;
	mMax = max;
	fontSize = _fontSize;
	maxChars = _maxChars;

	ci::TextBox ciTextBox = ci::TextBox();
	ciTextBox.setPremultiplied(true);

	ciTextBox.size(ivec2(ci::TextBox::GROW, ci::TextBox::GROW));
	ciTextBox.color(ColorA(0, 0, 0, 1));

	ciTextBox.setBackgroundColor(ColorA(1, 0, 0));
	ciTextBox.setAlignment(ci::TextBox::Alignment::LEFT);
	ciTextBox.font(CACHE()->getFont("fonts/Inconsolata.otf", fontSize));
	ciTextBox.text("a");
	charSizeFirst= ciTextBox.measure();

	ciTextBox.text("aB");
	charSizeNext = ciTextBox.measure();
	charSizeNext.x -= charSizeFirst.x;

	cursorOffset = (charSizeFirst.x - charSizeNext.x) *0.4 ;
	
	textSize = vec2(charSizeFirst.x + charSizeNext.x* (maxChars-1), charSizeFirst.y);
	boxSize = vec2(textSize.x + margin.x * 2, textSize.y + margin.y * 2);


	
	mShape = po::scene::ShapeView::createRoundedRect(boxSize.x, boxSize.y,8);
	mShape->setFillColor(Color::gray(0.6));
	mShape->setStrokeEnabled(true);
	mShape->setStrokeColor(ColorA(1,0,0,1));
	addSubview(mShape);

	selectShape = po::scene::ShapeView::createRect(1, charSizeFirst.y);
	selectShape->setFillColor(Color::gray(0.7));
	
	
	addSubview(selectShape);
	selectShape->setVisible( false);

	cursor = po::scene::ShapeView::createRect(2,charSizeFirst.y);
	cursor->setFillColor(Color::gray(0.0));
	
	cursor->setVisible(false);

	

}
void TextInput::clear()
{
	text = "";
	cursorPos = 0;
	redrawText();
	changeCursor();
	cursor->setVisible(false);

}
bool TextInput::checkValue()
{
	float val;
	bool isOk = true;
	try { val = std::stof(text); }
	catch(...)
	{
		isOk = false;
		val = -10000000;
	}

	std::size_t found = text.find(".");
	if (found != string::npos) 
	{
		 found = text.find(".",found+1);
		if (found != string::npos)
		{
			isOk = false;
		}
	}
	if (val<mMin || val >mMax) isOk = false;



	if (!isOk) 
	{
		mShape->setFillColor(Color(0.9, 0.5, 0.5));
	}
	return isOk;
}
float TextInput::getValue() 
{
	return std::stof(text);
}
void TextInput::redrawText()
{
	
	ci::TextBox ciTextBox = ci::TextBox();
	ciTextBox.setPremultiplied(true);

	ciTextBox.size(ivec2(ci::TextBox::GROW, ci::TextBox::GROW));
	ciTextBox.color(ColorA(0, 0, 0, 1));
	ciTextBox.text(text);
	ciTextBox.setBackgroundColor(ColorA(0, 0, 0,0));
	ciTextBox.setAlignment(ci::TextBox::Alignment::LEFT);

	ciTextBox.font(CACHE()->getFont("fonts/Inconsolata.otf", fontSize));

	Surface mSurface = ciTextBox.render();

	gl::TextureRef r = gl::Texture::create(mSurface);
	if (!textView) {
		textView = po::scene::ImageView::create(r);
		textView->setPosition(margin.x, margin.y);
		
		addSubview(textView);
		addSubview(cursor);
	}
	else {
		textView->setTexture(r);
		
		
	}
	
	
		
	
}
void TextInput::changeCursor()
{
	cursor->setPosition((charSizeNext.x*(cursorPos)) + cursorOffset + margin.x, margin.y);
	cursor->setVisible(true);
	nextCursorSwitchTime = getElapsedSeconds() + 0.5;
	addSubview(cursor);
}
void TextInput::setFocus(bool focus) 
{

	if (!focus) { 
		mShape->setFillColor(Color::gray(0.7));
		cursor->setVisible(false);
	}
	else { 
		mShape->setFillColor(Color::gray(0.8)); 
		changeCursor();
	}
}
void TextInput::keyDown(ci::app::KeyEvent event) 
{
	
	bool updateText = true;
	int code = event.getCode();
	if (isSelected) 
	{
	
		text.erase(text.begin() + selectStart, text.begin() + selectStart+selectSize);
		stopSelection();
		cursorPos = selectStart;
		changeCursor();
		
	}
	if (code == KeyEvent::KEY_BACKSPACE)
	{
		if (cursorPos > 0)
		{
			text.erase(text.begin() + cursorPos - 1, text.begin() + cursorPos);
			cursorPos--;
		}
		changeCursor();
	}
	else if (code == KeyEvent::KEY_LEFT)
	{
		cursorPos--;
		if (cursorPos < 0)cursorPos = 0;
		changeCursor();
	}
	else if (code == KeyEvent::KEY_RIGHT)
	{
		cursorPos++;
		if (cursorPos >= text.size())cursorPos = text.size();
		changeCursor();
	}
	else if (code == KeyEvent::KEY_COMMA)
	{

		addAddCursorPos(".", cursorPos);
		
	}
	else if (code == KeyEvent::KEY_KP_PERIOD)
	{
		addAddCursorPos(".", cursorPos);
	}
	else if (code == KeyEvent::KEY_PERIOD)
	{
		addAddCursorPos(".", cursorPos);
	}
	else if (code >= KeyEvent::KEY_0 && event.getCode() <= KeyEvent::KEY_9)
	{
		int num = code - KeyEvent::KEY_0;
		addAddCursorPos(to_string(num), cursorPos);
	}
	else if (code >= KeyEvent::KEY_KP0 && event.getCode() <= KeyEvent::KEY_KP9)
	{
		int num = code - KeyEvent::KEY_KP0;
		addAddCursorPos(to_string(num), cursorPos);
	}
	else 
	{
		updateText = false;
	}

	if (code == KeyEvent::KEY_KP_ENTER || code == KeyEvent::KEY_RETURN)
	{
		mSignalPressed.emit();
	}

	if (updateText) 
	{
		redrawText();
	}


}

void TextInput::addAddCursorPos(string in, int pos)
{
	if (text.size() == maxChars)return;
	string strfront = text.substr(0, cursorPos);
	string strback = text.substr(cursorPos);
	text = strfront + in + strback;
	cursorPos++;
	changeCursor();
}
void TextInput::setSelect(int start, int size) 
{
	isSelected = true;


	cursor->setVisible(false);
	selectStart = start;
	selectSize = size;
	selectShape->setVisible(true);
	selectShape->setPosition(charSizeNext.x*start+ cursorOffset + margin.x, margin.y);
	selectShape->setScale(charSizeNext.x*size, 1);

}
void TextInput::stopSelection()
{
	isSelected = false;

	selectShape->setVisible(false);


}
void TextInput::mouseDown(po::scene::MouseEvent& event)
{
	if (lastMouseDown + 0.4 > getElapsedSeconds() && text.size()>0)
	{
		
		setSelect(0, text.size());
		lastMouseDown = getElapsedSeconds();
		return;
	}
	else 
	{
		stopSelection();
	}

	lastMouseDown = getElapsedSeconds();
	vec2 mousePos =event.getLocalPos();
	float mouseX = mousePos.x;

	int cursorPosTemp = (mouseX - cursorOffset - margin.x) / charSizeNext.x;
	if (cursorPosTemp < 0)cursorPosTemp  = 0;
	if (cursorPosTemp  > text.size())cursorPosTemp  = text.size();
	
	cursorPos = cursorPosTemp;
	changeCursor();
}

void TextInput::update() 
{
	
	if (hasFocus) 
	{
		if (!isSelected)
		{
			if (getElapsedSeconds() > nextCursorSwitchTime)
			{
				if (cursor->isVisible())
				{
					cursor->setVisible(false);
				}
				else
				{
					cursor->setVisible(true);
				}
				nextCursorSwitchTime = getElapsedSeconds() + 0.5;
			}
		}
	}

}