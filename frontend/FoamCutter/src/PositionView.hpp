//
//  PositionView.hpp
//  Controler
//
//  Created by Kris Temmerman on 11/06/2019.
//

#pragma once

#include "poScene/ImageView.h"
#include "poScene/TextView.h"

class PositionView;
typedef std::shared_ptr<PositionView> PositionViewRef;


class PositionView: public po::scene::View
{
    
    
public:
    static PositionViewRef create();
    void setup();
    void update();
    void setNewPosition(float pos);
    void setText(std::string text);
      void setTextRaw(float rawPos);
    float smoothPosIn=0;
    po::scene::ViewRef distanceHolder;
};

