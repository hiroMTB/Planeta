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
        
        void updateCameraSettings(float & fake);
        
        ofEasyCam cam;
        ofxAssimpModelLoader model;

        ofParameterGroup  domePrms;
        ofParameter<bool> drawModel;
        ofParameter<float> nearClip;
        ofParameter<float> farClip;
        ofParameter<float> fov;
    };
}
