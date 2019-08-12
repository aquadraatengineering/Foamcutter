#pragma once
#include "poScene/View.h"







class Clickable : public po::scene::View {

public:



	// Id
	int mEventId = -1;;
	// Connections storage
	ci::signals::ConnectionList mConnections;




	Clickable();
	void setupClickable();


	// event stuff
	bool mPropagationEnabled = true;
	void _mouseDownInside(po::scene::MouseEvent& event);
	void _mouseUp(po::scene::MouseEvent& event);
	void _mouseDrag(po::scene::MouseEvent& event);
	virtual void mouseDown(po::scene::MouseEvent& event);
	virtual void mouseUp(po::scene::MouseEvent& event);
	virtual void mouseDrag(po::scene::MouseEvent& event);
	bool hasFocus = false;
	void _setFocus(bool fo);
	virtual void setFocus(bool fo) {};


	virtual void keyDown(ci::app::KeyEvent event) {};
};