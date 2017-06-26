#pragma once

#include "ofMain.h"
#include "ofxTextureRecorder.h"
#include "Renderable.h"
#include "ofxAssimpModelLoader.h"

namespace mikromedas{

    class DomeView : public ofBaseApp, public Renderable{
        
    public:
        DomeView(int w, int h, string path);
        virtual ~DomeView(){cout << " - Destruct DomeView"; };
        virtual void setup(){};
        virtual void update(){};
        virtual void draw(){};
        virtual void exit(){};
        
        void setupModel();
        void setupCameraGui();
        
        void resetCamera();
        void updateCameraSettings();
        void floatCb(float & fake);
        void vec2Cb(glm::vec2 & fake);
        void vec3Cb(glm::vec3 & fake);

        void drawModelWireframe();
        void drawModelTextured(const ofTexture & tex);
        
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
        
        void bindMyTexture(const ofTexture & tex);
        void unbindMyTexture(const ofTexture & tex);
    };
}
