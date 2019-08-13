//
//  LogView.cpp
//  Controler
//
//  Created by Kris Temmerman on 11/06/2019.
//

#include "LogView.hpp"
#include "Log.hpp"

#include "AssetsCache.h"
using namespace po::scene;
using namespace ci;
using namespace ci::app;
using namespace std;
LogViewRef LogView::create()
{
    LogViewRef ref(new LogView());
    ref->setup();
    return ref;
}

void LogView::setup()
{
	bg = po::scene::ShapeView::createRoundedRect(420, 960, 8);
	bg->setFillColor(Color::gray(0.5));
	bg->setPosition(-20, -20);
	addSubview(bg);
    
}
void LogView::makeLog()
{
    
    removeAllSubviews();
	addSubview(bg);
    int l =LOG()->logData.size();
    int pos =0;
	
    for(int i=l-1;i>=max(0,l-30); i--)
    {
        addLogText(LOG()->logData[i].first,LOG()->logData[i].second,pos );
        
        pos+=25;
    }
    
}
void LogView::addLogText(std::string text,int type,int pos)
{
    ci::TextBox ciTextBox = ci::TextBox();
    ciTextBox.setPremultiplied(true);
    
    ciTextBox.size(ivec2(ci::TextBox::GROW, ci::TextBox::GROW));
    if(type==1){
        ciTextBox.color(ColorA(1, 0, 0, 1));
    }else
    {
        ciTextBox.color(ColorA(0, 1, 0, 1));
        
    }
    ciTextBox.text(text);
    ciTextBox.setBackgroundColor(Color::gray(0.5));
    ciTextBox.setAlignment(ci::TextBox::Alignment::LEFT);
    
    ciTextBox.font(CACHE()->getFont("fonts/Inconsolata.otf", 20));
    
    Surface mSurface = ciTextBox.render();
    gl::TextureRef r = gl::Texture::create(mSurface);
    ImageViewRef disclaimerText = po::scene::ImageView::create(r);
    disclaimerText->setAlignment(Alignment::TOP_LEFT);
    
    disclaimerText->setPosition(0, pos);
    //disclaimerText->setMovable();
    addSubview(disclaimerText);
    
}
void LogView::update()
{
    
    if(LOG()->logDirty)
    {
        makeLog();
        LOG()->logDirty =false;
    }
    
    
}
