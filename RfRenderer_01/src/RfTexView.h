#pragma once

#include "Renderer.h"
#include "TexView.h"

using namespace mikromedas;

class RfTexView : public TexView{

public:
    
    RfTexView(int w, int h, string path);
    virtual ~RfTexView(){ cout << "Destruct RfTexView"; }
    
    virtual void setup() override;
    virtual void update() override;
    virtual void draw() override;
    virtual void exit() override;
    
    ofxPanel gui;
    Renderer renderer;
};
