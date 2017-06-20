#pragma once

#include "ofMain.h"
#include "EasingPrm.h"
#include "ofxGui.h"
#include "TexView.h"
#include "DomeView.h"

using namespace mikromedas;

class ofApp : public ofBaseApp{
    
public:
    
    static ofApp * get(){
        static ofApp * app = new ofApp();
        return app;
    }
    
    void setup();
    void draw();
    void update();
    void keyPressed(int key);
    void exit();
    
    int frame = -1;
    ofxPanel gui;
    vector<EasingPrm> anim;
    
    shared_ptr<TexView> texView;
    shared_ptr<DomeView> domeView;
};

