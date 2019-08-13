//
//  PositionView.cpp
//  Controler
//
//  Created by Kris Temmerman on 11/06/2019.
//

#include "PositionView.hpp"

#include "SerialHandler.hpp"
#include "GlobalSettings.h"
#include "AssetsCache.h"
using namespace po::scene;
using namespace ci;
using namespace ci::app;
using namespace std;
PositionViewRef PositionView::create()
{
    PositionViewRef ref(new PositionView());
    ref->setup();
    return ref;
}

void PositionView::setup()
{
    ci::TextBox ciTextBox = ci::TextBox();
    ciTextBox.setPremultiplied(true);
    ciTextBox.size(ivec2(ci::TextBox::GROW, ci::TextBox::GROW));
    ciTextBox.color(ColorA(1, 1, 1, 1));
    ciTextBox.text("mm");
    ciTextBox.setBackgroundColor(Color(0, 0, 0));
    ciTextBox.setAlignment(ci::TextBox::Alignment::LEFT);
    ciTextBox.font(CACHE()->getFont("fonts/Inconsolata.otf", 40));
    
    Surface mSurface = ciTextBox.render();
    gl::TextureRef r = gl::Texture::create(mSurface);
    ImageViewRef disclaimerText = po::scene::ImageView::create(r);
    disclaimerText->setAlignment(Alignment::TOP_RIGHT);
    disclaimerText->setPosition(400, 55);
    addSubview(disclaimerText);
    
    distanceHolder = View::create();
    addSubview(distanceHolder);
   setText("-----");
}

void PositionView::setNewPosition(float posIn)
{
    distanceHolder->removeAllSubviews();
    
    
    smoothPosIn +=(posIn-smoothPosIn)/10;
    setTextRaw(smoothPosIn);
    float pos =smoothPosIn;


    pos+=GS()->heightOffset.value();
    
    float rangeInput =GS()->maxDistInput.value() -GS()->minDistInput.value();
    pos -=GS()->minDistInput.value();
    pos/= rangeInput;
    
     float range=GS()->maxDist.value() -GS()->minDist.value();
    pos*=range;
    pos+=GS()->minDist.value();
    if(pos>610.f)
    {
        setText("OFR");
        
    }  if(pos<84.f)
    {
        setText("OFR");
        
    }else{
      
    
    std::ostringstream out;
    out.precision(1);
    out << std::fixed <<pos;
    
    setText(out.str());
    }


}

void PositionView::setText(std::string text)
{
    ci::TextBox ciTextBox = ci::TextBox();
    ciTextBox.setPremultiplied(true);
    
    ciTextBox.size(ivec2(ci::TextBox::GROW, ci::TextBox::GROW));
    if(SERIAL()->targetState==0){
    ciTextBox.color(ColorA(1, 1, 1, 1));
    }else if(SERIAL()->targetState==1)
    {
          ciTextBox.color(ColorA(1, 0, 0, 1));
        
    }else if(SERIAL()->targetState==2)
    {
        ciTextBox.color(ColorA(0, 1, 0, 1));
        
    }
   
    ciTextBox.text(text);
  //  ciTextBox.setBackgroundColor(Color(0, 0, 0));
    ciTextBox.setAlignment(ci::TextBox::Alignment::LEFT);
    
    ciTextBox.font(CACHE()->getFont("fonts/Inconsolata.otf", 100));
    
    Surface mSurface = ciTextBox.render();
    gl::TextureRef r = gl::Texture::create(mSurface);
    ImageViewRef disclaimerText = po::scene::ImageView::create(r);
    disclaimerText->setAlignment(Alignment::TOP_RIGHT);
    
    disclaimerText->setPosition(300, 0);
    
    distanceHolder->addSubview(disclaimerText);
    
}
void PositionView::setTextRaw(float rawPos)
{
    ci::TextBox ciTextBox = ci::TextBox();
    ciTextBox.setPremultiplied(true);
    
    ciTextBox.size(ivec2(ci::TextBox::GROW, ci::TextBox::GROW));
    
    //ciTextBox.color(ColorA(1, 1, 1, 1));
    
    std::ostringstream out;
    out.precision(1);
    out << std::fixed <<rawPos;
    
    ciTextBox.text(out.str()+" raw");
    ciTextBox.setBackgroundColor(Color(0, 0, 0));
    ciTextBox.setAlignment(ci::TextBox::Alignment::LEFT);
    
    ciTextBox.font(CACHE()->getFont("fonts/Inconsolata.otf", 20));
    
    Surface mSurface = ciTextBox.render();
    gl::TextureRef r = gl::Texture::create(mSurface);
    ImageViewRef disclaimerText = po::scene::ImageView::create(r);
    disclaimerText->setAlignment(Alignment::TOP_RIGHT);
    
    disclaimerText->setPosition(400, 100);
    
    distanceHolder->addSubview(disclaimerText);
    
}
void PositionView::update()
{
    if(SERIAL()->positionIsDirty)
    {
        setNewPosition(SERIAL()->currentPosition);
        SERIAL()->positionIsDirty =false;
    }
}
