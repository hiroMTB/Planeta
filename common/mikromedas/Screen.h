#pragma once

#include "ofMain.h"

//#define MAX_QUALITY 1

namespace mikromedas{
    
    struct Screen{
    public:
#ifdef MAX_QUALITY
        static constexpr float renderW = 1920*4;
        static constexpr float renderH = 1920*4;
        static constexpr float centerX = renderW/2;
        static constexpr float centerY = renderH/2;
        static constexpr int fps = 25;
#else
        static constexpr float renderW = 1024*2;
        static constexpr float renderH = 1024*2;
        static constexpr float centerX = renderW/2;
        static constexpr float centerY = renderH/2;
        static constexpr int fps = 25;
#endif
    };
}
