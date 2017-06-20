#pragma once

#include "ofMain.h"
#include "ofxTextureRecorder.h"
#include "Renderable.h"
#include "ofxAssimpModelLoader.h"

namespace mikromedas{

    class DomeView : public ofBaseApp, public Renderable{
        
    public:
        DomeView(int w, int h, string path);

        void setup();
        void update();
        void draw();
        void exit();
        
        ofEasyCam cam;
        ofxAssimpModelLoader model;

        ofParameterGroup   parameters2;
        ofxPanel gui2;
        ofParameter<bool> drawModel;
    };
}
