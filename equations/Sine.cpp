//
//  Sine.cpp
//
//  This code is derived from Universal Tween Engine
//  Licensed under Apache License 2.0 - http://www.apache.org/licenses/LICENSE-2.0
//

#include <math.h>
#include "Sine.h"

namespace TweenEngine
{
    float SineIn::compute(float t) { return (float)-cos(t * (M_PI/2)) + 1; }
    const char *SineIn::toString() { return "Sine.IN"; }
    
    float SineOut::compute(float t) { return (float)sin(t * (M_PI/2)); }
    const char *SineOut::toString() { return "Sine.OUT"; }
    
    float SineInOut::compute(float t) { return -0.5f * ((float)cos(M_PI*t) - 1); }
    const char *SineInOut::toString() { return "Sine.INOUT"; }
}
