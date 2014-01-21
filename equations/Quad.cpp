//
//  Quad.cpp
//
//  This code is derived from Universal Tween Engine
//  Licensed under Apache License 2.0 - http://www.apache.org/licenses/LICENSE-2.0
//

/**
 * Easing equation based on Robert Penner's work:
 * http://robertpenner.com/easing/
 * @author Aurelien Ribon | http://www.aurelienribon.com/
 */

#include "Quad.h"

namespace TweenEngine
{
    float QuadIn::compute(float t) { return t*t; }
    const char *QuadIn::toString() { return "Quad.IN"; }

    float QuadOut::compute(float t) { return -t*(t-2); }
    const char *QuadOut::toString() { return "Quad.OUT"; }

    float QuadInOut::compute(float t)
    {
        t*=2;
        if (t < 1) return 0.5f*t*t;
        return -0.5f * ((t-1)*(t-3) - 1);
    }
    const char *QuadInOut::toString() { return "Quad.INOUT"; }
}
