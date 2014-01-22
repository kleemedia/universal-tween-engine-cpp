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
    
    TweenEquation &TweenEquations::easeInOutLinear = *(new LinearInOut());

    TweenEquation &TweenEquations::easeInBack = *(new BackIn());
    TweenEquation &TweenEquations::easeOutBack = *(new BackOut());
    TweenEquation &TweenEquations::easeInOutBack = *(new BackInOut());
    
    TweenEquation &TweenEquations::easeInBounce = *(new BounceIn());
    TweenEquation &TweenEquations::easeOutBounce = *(new BounceOut());
    TweenEquation &TweenEquations::easeInOutBounce = *(new BounceInOut());

    TweenEquation &TweenEquations::easeInCirc = *(new CircIn());
    TweenEquation &TweenEquations::easeOutCirc = *(new CircOut());
    TweenEquation &TweenEquations::easeInOutCirc = *(new CircInOut());

    TweenEquation &TweenEquations::easeInCubic = *(new CubicIn());
    TweenEquation &TweenEquations::easeOutCubic = *(new CubicOut());
    TweenEquation &TweenEquations::easeInOutCubic = *(new CubicInOut());
    
    TweenEquation &TweenEquations::easeInElastic = *(new ElasticIn());
    TweenEquation &TweenEquations::easeOutElastic = *(new ElasticOut());
    TweenEquation &TweenEquations::easeInOutElastic = *(new ElasticInOut());
    
    TweenEquation &TweenEquations::easeInExpo = *(new ExpoIn());
    TweenEquation &TweenEquations::easeOutExpo = *(new ExpoOut());
    TweenEquation &TweenEquations::easeInOutExpo = *(new ExpoInOut());
    
    TweenEquation &TweenEquations::easeInQuart = *(new QuartIn());
    TweenEquation &TweenEquations::easeOutQuart = *(new QuartOut());
    TweenEquation &TweenEquations::easeInOutQuart = *(new QuartInOut());

    TweenEquation &TweenEquations::easeInQuint = *(new QuintIn());
    TweenEquation &TweenEquations::easeOutQuint = *(new QuintOut());
    TweenEquation &TweenEquations::easeInOutQuint = *(new QuintInOut());
    
    TweenEquation &TweenEquations::easeInSine = *(new SineIn());
    TweenEquation &TweenEquations::easeOutSine = *(new SineOut());
    TweenEquation &TweenEquations::easeInOutSine = *(new SineInOut());
}