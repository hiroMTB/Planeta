#pragma once

#include "ofMain.h"

//#define MAX_QUALITY 1

namespace ScreenDef{

#ifdef MAX_QUALITY
    const static float renderW = 1920*4;
    const static float renderH = 1920*4;
    const static float centerX = renderW/2;
    const static float centerY = renderH/2;
    const static int fps = 25;
#else
    const static float renderW = 1024;
    const static float renderH = 1024;
    const static float centerX = renderW/2;
    const static float centerY = renderH/2;
    const static int fps = 25;
#endif

};
