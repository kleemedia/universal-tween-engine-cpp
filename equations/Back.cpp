//
//  Back.cpp
//
//  This code is derived from Universal Tween Engine
//  Licensed under Apache License 2.0 - http://www.apache.org/licenses/LICENSE-2.0
//

#include "Back.h"

#define S   (1.70158f)

namespace TweenEngine
{
    float BackIn::compute(float t) { return t*t*((S+1)*t - S); }
    const char *BackIn::toString() { return "Back.IN"; }
    
    float BackOut::compute(float t) {
        t -= 1;
        return (t*t*((S+1)*t + S) + 1);
    }
    const char *BackOut::toString() { return "Back.OUT"; }
    
    float BackInOut::compute(float t) {
        float s=S*1.525;
        t*=2;
        if (t < 1) {
            return 0.5f*(t*t*((s+1)*t - s));
        } else {
            t -= 2;
            return 0.5f*(t*t*((s+1)*t + s) + 2);
        }
    }
    const char *BackInOut::toString() { return "Back.INOUT"; }
}
