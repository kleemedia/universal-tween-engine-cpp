//
//  Linear.cpp
//  This code is derived from Universal Tween Engine
//  Licensed under Apache License 2.0 - http://www.apache.org/licenses/LICENSE-2.0
//

/**
 * Easing equation based on Robert Penner's work:
 * http://robertpenner.com/easing/
 * @author Aurelien Ribon | http://www.aurelienribon.com/
 */

#include "Linear.h"

namespace TweenEngine
{
    float LinearInOut::compute(float t) { return t; }
    const char *LinearInOut::toString() { return "Linear.INOUT"; }

}