#pragma once

#include "ofMain.h"
#include "mikromedas/HemiSphere.h"

using namespace mikromedas;

class ofApp : public ofBaseApp{
    
public:
    static ofApp * get(){
        static ofApp * app = new ofApp();
        return app;
    }
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    void bindMyTexture(const ofTexture & tex);
    void unbindMyTexture(const ofTexture & tex);
    
    ofEasyCam cam;
    int frame;
    
    ofHemiSpherePrimitive hemi;
    ofSpherePrimitive sphere;
    ofImage img;
    
    bool bWire;
};
