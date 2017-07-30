#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#include "mikromedas/Renderer.h"
#include "mtb/EasingPrm.h"

using namespace mikromedas;
using namespace mtb;

class ofApp : public ofBaseApp{
    
public:
    
    static ofApp * get(){
        static ofApp * app = new ofApp();
        return app;
    }
    
    void setup();
    void draw();
    void update();
    void keyPressed(int key){};
    void exit();
    
    Renderer renderer;
    ofFbo fbo;
    
    int frame = -1;
    
    vector<mtb::EasingPrm> anim;

    ofxPanel gui;
};

