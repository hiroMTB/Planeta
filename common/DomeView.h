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
        
        void resetCamera();
        void updateCameraSettings();
        void floatCb(float & fake);
        void vec2Cb(glm::vec2 & fake);
        void vec3Cb(glm::vec3 & fake);
        
        ofEasyCam cam;
        ofxAssimpModelLoader model;

        ofParameterGroup  domePrms;
        ofParameter<bool> bDrawWireFrame;
        ofParameter<bool> bDrawFaces;
        
        ofParameter<float> nearClip;
        ofParameter<float> farClip;
        ofParameter<float> fov;
        ofParameter<float> distance;
        ofParameter<float> pan;
        ofParameter<float> tilt;
        ofParameter<float> roll;

        ofParameter<glm::vec2> lensOffset;
        ofParameter<void> resetCameraBtn;
        float prevPan = 0;
        float prevTilt = 0;
        float prevRoll = 0;
        
        ofImage img;
        
        void bindMyTexture();
        void unbindMyTexture();
    };
}
