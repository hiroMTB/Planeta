#pragma once

#include "mikromedas/DomeView.h"
#include "mikromedas/Renderer.h"

class RfView : public mikromedas::DomeView{
    
public:
    
    RfView(int w, int h, string path);
    virtual ~RfView(){ cout << "Destruct RfView"; }
    
    virtual void setup() override;
    virtual void update() override;
    virtual void draw() override;

    void drawScene();
    
    ofVboMesh points;
    ofVboMesh lines;
    
    ofImage img;

    ofxPanel gui;
    mikromedas::Renderer renderer;
    
    ofParameterGroup prms;
    ofParameter<float> rotAngle;
    ofParameter<glm::vec3> rotAxis;
    
    ofSpherePrimitive sphere;
};

