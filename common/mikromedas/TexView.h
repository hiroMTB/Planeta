#pragma once

#include "ofMain.h"
#include "ofxGui.h"

namespace mikromedas{

    class TexView : public ofBaseApp{
        
    public:
        TexView(){};
        virtual ~TexView(){ cout << "destruct TexView "; }
        virtual void setup(){};
        virtual void update(){};
        virtual void draw(){};
        virtual void exit(){};
        
        void drawGuide();
        void setupGui(ofxPanel & gui);
        ofParameterGroup  texPrms;
        ofParameter<bool> bDrawGuide;
        
        ofImage mask;
    };
}
