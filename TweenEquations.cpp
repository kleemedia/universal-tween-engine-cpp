//
//  Equations.cpp
//
//  This code is derived from Universal Tween Engine
//  Licensed under Apache License 2.0 - http://www.apache.org/licenses/LICENSE-2.0
//

#include "TweenEquations.h"

namespace TweenEngine
{
    TweenEquation &TweenEquations::easeInQuad = *(new QuadIn());
    TweenEquation &TweenEquations::easeOutQuad = *(new QuadOut());
    TweenEquation &TweenEquations::easeInOutQuad = *(new QuadInOut());
    
}