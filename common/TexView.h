#pragma once

#include "ofMain.h"
#include "ofxTextureRecorder.h"
#include "Renderable.h"

namespace mikromedas{

    class TexView : public ofBaseApp, public Renderable{
        
    public:
        TexView(int w, int h, string path);
        void setup();
        void update();
        void draw();
        void exit();
    };
}
