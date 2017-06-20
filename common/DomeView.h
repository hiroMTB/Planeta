#pragma once

#include "ofMain.h"
#include "ofxTextureRecorder.h"
#include "Renderable.h"

namespace mikromedas{

    class DomeView : public ofBaseApp, public Renderable{
        
    public:
        DomeView(int w, int h, string path);

        void setup();
        void update();
        void draw();
        void exit();
    };
}
