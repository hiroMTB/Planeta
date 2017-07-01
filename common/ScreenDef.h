#pragma once

#include "ofMain.h"

namespace ScreenDef{

#ifdef MAX_QUALITY
    const static float renderW = 8000;
    const static float renderH = 8000;
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
