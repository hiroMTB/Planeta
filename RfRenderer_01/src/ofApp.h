#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#include "mtb/EasingPrm.h"
#include "RfTexView.h"
#include "RfView.h"

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
    
    ofxPanel gui;
    vector<mtb::EasingPrm> anim;
    
    shared_ptr<RfTexView> texView;
    shared_ptr<RfView> rfView;
    
    ofParameterGroup mainPrms;
    ofParameter<bool> bStart;
    ofParameter<int> frame;

};

