#pragma once

#include "DomeView.h"
#include "RfImporterBin.h"

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

    ofParameterGroup rfPrms;
    ofParameter<bool> bStart;
    ofParameter<int> simFrame;
    ofParameter<int> numParticles;
};

