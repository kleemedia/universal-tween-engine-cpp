//
//  Cubic.cpp
//
//  This code is derived from Universal Tween Engine
//  Licensed under Apache License 2.0 - http://www.apache.org/licenses/LICENSE-2.0
//

#include "Cubic.h"

namespace TweenEngine
{
    float CubicIn::compute(float t) { return t*t*t; }
    const char *CubicIn::toString() { return "Cubic.IN"; }
    
    float CubicOut::compute(float t) {
        t -= 1;
        return t*t*t + 1;
    }
    const char *CubicOut::toString() { return "Cubic.OUT"; }
    
    float CubicInOut::compute(float t) {
        t *= 2;
        if (t < 1) {
            return 0.5f * t*t*t;
        } else {
            t -= 2;
            return 0.5f * (t*t*t + 2);
        }
    }
    const char *CubicInOut::toString() { return "Cubic.INOUT"; }
}
