//
//  Quint.cpp
//
//  This code is derived from Universal Tween Engine
//  Licensed under Apache License 2.0 - http://www.apache.org/licenses/LICENSE-2.0
//

#include "Quint.h"

namespace TweenEngine
{
    float QuintIn::compute(float t) { return t*t*t*t*t; }
    const char *QuintIn::toString() { return "Quint.IN"; }
    
    float QuintOut::compute(float t) {
        t-=1;
        return -(t*t*t*t*t - 1);
    }
    const char *QuintOut::toString() { return "Quint.OUT"; }
    
    float QuintInOut::compute(float t) {
        t *= 2;
        if (t < 1) {
            return 0.5f*t*t*t*t*t;
        } else {
            t -= 2;
            return -0.5f * (t*t*t*t*t - 2);
        }
    }
    const char *QuintInOut::toString() { return "Quint.INOUT"; }
}
