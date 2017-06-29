#pragma once

#include "DomeView.h"
#include "RfImporterBin.h"
#include "Renderer.h"

using namespace mikromedas;

class RfView : public DomeView{
    
public:
    
    RfView(int w, int h, string path);
    virtual ~RfView(){ cout << "Destruct RfView"; }
    
    virtual void setup() override;
    virtual void update() override;
    virtual void draw() override;
    virtual void exit() override;
    
    RfImporterBin rf;
    
    ofBufferObject buf;
    ofVboMesh mesh;
    
    ofImage img;

    ofxPanel gui;
    Renderer renderer;
    
    ofParameterGroup rfPrms;
    ofParameter<int> numParticles;
};

