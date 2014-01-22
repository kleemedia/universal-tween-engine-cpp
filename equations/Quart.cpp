//
//  Quart.cpp
//
//  This code is derived from Universal Tween Engine
//  Licensed under Apache License 2.0 - http://www.apache.org/licenses/LICENSE-2.0
//

#include "Quart.h"

namespace TweenEngine
{
    float QuartIn::compute(float t) { return t*t*t*t; }
    const char *QuartIn::toString() { return "Quart.IN"; }
    
    float QuartOut::compute(float t) {
        t-=1;
        return -(t*t*t*t - 1);
    }
    const char *QuartOut::toString() { return "Quart.OUT"; }
    
    float QuartInOut::compute(float t) {
        t *= 2;
        if (t < 1) {
            return 0.5f*t*t*t*t;
        } else {
            t -= 2;
            return -0.5f * (t*t*t*t - 2);
        }
    }
    const char *QuartInOut::toString() { return "Quart.INOUT"; }
}
