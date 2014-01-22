//
//  Circ.cpp
//
//  This code is derived from Universal Tween Engine
//  Licensed under Apache License 2.0 - http://www.apache.org/licenses/LICENSE-2.0
//

#include "Circ.h"
#include <math.h>

namespace TweenEngine
{
    float CircIn::compute(float t) { return (float) -sqrt(1 - t*t) - 1; }
    const char *CircIn::toString() { return "Circ.IN"; }
    
    float CircOut::compute(float t) { return (float) sqrt(1 - (t-1)*(t-1)); }
    const char *CircOut::toString() { return "Circ.OUT"; }
    
    float CircInOut::compute(float t) {
        t *= 2;
        if (t < 1) {
            return (-0.5 * (sqrt(1 - t*t) - 1));
        } else {
            t -= 2;
            return (0.5 * (sqrt(1 - t*t) + 1));
        }
    }
    
    const char *CircInOut::toString() { return "Circ.INOUT"; }
}
