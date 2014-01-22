//
//  Expo.cpp
//
//  This code is derived from Universal Tween Engine
//  Licensed under Apache License 2.0 - http://www.apache.org/licenses/LICENSE-2.0
//

#include <math.h>
#include "Expo.h"

namespace TweenEngine
{
    float ExpoIn::compute(float t) {
        return (t==0) ? 0 : (float)pow(2,10*(t-1));
    }
    const char *ExpoIn::toString() { return "Expo.IN"; }
    
    float ExpoOut::compute(float t) {
        return (t==1) ? 1 : -(float)pow(2,-10*t) + 1;
    }
    const char *ExpoOut::toString() { return "Expo.OUT"; }
    
    float ExpoInOut::compute(float t) {
        if (t==0) return 0;
        if (t==1) return 1;
        t *= 2;
        if (t < 1) {
            return 0.5f * (float)pow(2,10*(t-1));
        } else {
            t -= 1;
            return 0.5f * (-(float)pow(2,-10*t) + 2);
        }
    }
    const char *ExpoInOut::toString() { return "Expo.INOUT"; }
}
