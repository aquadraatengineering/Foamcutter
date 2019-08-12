#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "MainViewController.hpp"
#include "poScene/Scene.h"
#include "FocusManager.h"
#include "SerialHandler.hpp"

using namespace ci;
using namespace ci::app;
using namespace std;

class FoamCutterApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
	void keyDown(KeyEvent event) override;
	po::scene::SceneRef            mScene;
	MainViewControllerRef        mMainViewController;
};

void FoamCutterApp::setup()
{
	setWindowSize(vec2(1920, 1080));
	setWindowPos(vec2(20, 20));
	//setFullScreen(true);
	mMainViewController = MainViewController::create();
	mScene = po::scene::Scene::create(mMainViewController);
	SERIAL()->setup();
}

void FoamCutterApp::mouseDown( MouseEvent event )
{
}
void FoamCutterApp::keyDown(KeyEvent event)
{
	if (event.getCode() == KeyEvent::KEY_f) 
	{
		setFullScreen(!isFullScreen());
	}
	FOCUS()->keyDown(event);
}
void FoamCutterApp::update()
{
	SERIAL()->update();
	mScene->update();
}

void FoamCutterApp::draw()
{

	gl::clear( Color( 0, 0, 0 ) ); 
	mScene->draw();
}

CINDER_APP( FoamCutterApp, RendererGl )
