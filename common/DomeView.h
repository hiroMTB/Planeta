#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofxGui.h"

namespace mikromedas{

    class DomeView : public ofBaseApp{
        
    public:
        DomeView(){};
        virtual ~DomeView(){cout << " - Destruct DomeView"; };
        virtual void setup(){};
        virtual void update(){};
        virtual void draw(){};
        virtual void exit(){};
        
        void setupModel();
        void setupCameraGui(ofxPanel & gui);
        
        void resetCamera();
        void updateCameraSettings();
        void drawTexDome(const ofTexture & tex);
        void drawWireDome(int res1, int res2);
        void bindMyTexture(const ofTexture & tex);
        void unbindMyTexture(const ofTexture & tex);

    private:
        void floatCb(float & fake);
        void vec2Cb(glm::vec2 & fake);
        void vec3Cb(glm::vec3 & fake);

    public:
        ofEasyCam cam;
        ofxAssimpModelLoader wire_dome;
        ofxAssimpModelLoader tex_dome;
        
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
    };
}
