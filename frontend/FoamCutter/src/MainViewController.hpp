//
//  MainViewControler.hpp
//  Controler
//
//  Created by Kris Temmerman on 11/06/2019.
//

#pragma once

#include "poScene/ViewController.h"
#include "poScene/ImageView.h"
#include "ManualInputVC.h"

class MainViewController;
typedef std::shared_ptr<MainViewController> MainViewControllerRef;

class MainViewController : public po::scene::ViewController
{
public:
    static MainViewControllerRef create();
    void setup();
	po::scene::ImageViewRef background;
	ManualInputVCRef manualInput;

};

