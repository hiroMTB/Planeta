#pragma once

#include "ofMain.h"
#include "ofxTextureRecorder.h"
#include "EasingPrm.h"

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
    
    ofxTextureRecorder recorder;
    ofFbo fbo;
    
    int frame = -1;
    
    vector<EasingPrm> anim;
};
