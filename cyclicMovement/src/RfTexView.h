#pragma once

#include "Renderer.h"
#include "TexView.h"
#include "ofxEquidistantProjection.h"

using namespace ofxequidistantprojection;

class RfTexView : public mikromedas::TexView{

public:
    
    RfTexView(int w, int h, string path);
    virtual ~RfTexView(){ cout << "Destruct RfTexView"; }
    
    virtual void setup() override;
    virtual void update() override;
    virtual void draw() override;
    virtual void exit() override;
    
    void mouseDragged(int x, int y, int button) override;

    ofxPanel gui;
    mikromedas::Renderer renderer;
    
    ofxEquidistantProjection equi;
};
