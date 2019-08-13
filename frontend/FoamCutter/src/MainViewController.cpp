//
//  MainViewControler.cpp
//  Controler
//
//  Created by Kris Temmerman on 11/06/2019.
//

#include "MainViewController.hpp"
#include "FocusManager.h"
#include "LogView.hpp"
#include "AssetsCache.h"
using namespace po::scene;

using namespace ci;
using namespace ci::app;
using namespace std;


MainViewControllerRef MainViewController::create()
{
    MainViewControllerRef ref =std::make_shared<MainViewController>();
    ref->setup();
    return ref;
}


void MainViewController::setup(){
    
	background = ImageView::create(CACHE()->getTexture("ui/background.png"));
	getView()->addSubview(background);

	manualInput = ManualInputVC::create();
	manualInput->setup();
	manualInput->getView()->setPosition(40, 40);
	getView()->addSubview(manualInput->getView());


	baseInput = BaseInputVC::create();
	baseInput->setup();
	baseInput->getView()->setPosition(40, 40+150);
	getView()->addSubview(baseInput->getView());


	LogViewRef l = LogView::create();
	l->setPosition(1500, 40);
	getView()->addSubview(l);

}


