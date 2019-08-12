//
//  LogView.hpp
//  Controler
//
//  Created by Kris Temmerman on 11/06/2019.
//

#pragma once

#include "poScene/ImageView.h"
#include "poScene/TextView.h"

class LogView;
typedef std::shared_ptr<LogView> LogViewRef;


class LogView: public po::scene::View
{
    
    
public:
    static LogViewRef create();
    void setup();
    void update();
    void makeLog();
    void addLogText(std::string text,int type,int pos);
};
