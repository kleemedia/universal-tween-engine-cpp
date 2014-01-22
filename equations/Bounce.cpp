//
//  Bounce.cpp
//
//  This code is derived from Universal Tween Engine
//  Licensed under Apache License 2.0 - http://www.apache.org/licenses/LICENSE-2.0
//

#include "Bounce.h"

namespace TweenEngine
{
    inline float outBounce(float t) {
        if (t < (1/2.75)) {
            return 7.5625f*t*t;
        } else if (t < (2/2.75)) {
            t = t - (1.5 / 2.75);
            return (7.5625 * t * t + 0.75);
        } else if (t < (2.5/2.75)) {
            t = t - (2.25 / 2.75);
            return (7.5625 * t * t + 0.9375);
        } else {
            t = t - (2.625 / 2.75);
            return (7.5625 * t * t + 0.984375);
        }
    }

    inline float inBounce(float t) {
        return 1 - outBounce(1-t);
    }
   
    float BounceIn::compute(float t) { return inBounce(t); }
    const char *BounceIn::toString() { return "Bounce.IN"; }
    
    float BounceOut::compute(float t) { return outBounce(t); }
    const char *BounceOut::toString() { return "Bounce.OUT"; }
    
    float BounceInOut::compute(float t) {
        if (t < 0.5f) return (inBounce(t*2) * 0.5f);
        else return (outBounce(t*2-1) * 0.5f + 0.5f);
    }
    const char *BounceInOut::toString() { return "Bounce.INOUT"; }
}
