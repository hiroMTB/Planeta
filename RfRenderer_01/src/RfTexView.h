#pragma once

#include "Renderer.h"
#include "TexView.h"
#include "ofxDomemaster.h"

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
    
    ofxDomemaster domemaster;
};
