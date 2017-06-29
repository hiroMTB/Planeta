#pragma once

#include "ofMain.h"
#include "EasingPrm.h"
#include "ofxGui.h"
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
    vector<EasingPrm> anim;
    
    shared_ptr<RfTexView> texView;
    shared_ptr<RfView> rfView;
    
    ofParameterGroup mainPrms;
    ofParameter<bool> bStart;
    ofParameter<int> frame;

};

