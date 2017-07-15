#pragma once

#include "mikromedas/DomeView.h"
#include "mikromedas/Renderer.h"
#include "mtb/RfImporterBin.h"

class RfView : public mikromedas::DomeView{
    
public:
    
    RfView(int w, int h, string path);
    virtual ~RfView(){ cout << "Destruct RfView"; }
    
    virtual void setup() override;
    virtual void update() override;
    virtual void draw() override;
    virtual void exit() override;

    void drawScene();
    
    mtb::RfImporterBin rf;
    
    ofVboMesh mesh;
    
    ofImage img;

    ofxPanel gui;
    mikromedas::Renderer renderer;
    
    ofParameterGroup rfPrms;
    ofParameter<int> numParticles;
};

