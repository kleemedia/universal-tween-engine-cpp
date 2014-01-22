//
//  TweenEquations.h
//
//  This code is derived from Universal Tween Engine
//  Licensed under Apache License 2.0 - http://www.apache.org/licenses/LICENSE-2.0
//

#ifndef __TweenEquations__
#define __TweenEquations__

#include "Quad.h"
#include "Linear.h"
#include "Back.h"
#include "Bounce.h"
#include "Circ.h"
#include "Cubic.h"
#include "Elastic.h"
#include "Expo.h"
#include "Quart.h"
#include "Quint.h"
#include "Sine.h"

namespace TweenEngine
{
    class TweenEquations
    {
    public:
        static TweenEquation &easeInQuad;
        static TweenEquation &easeOutQuad;
        static TweenEquation &easeInOutQuad;
        static TweenEquation &easeInOutLinear;
        static TweenEquation &easeInBack;
        static TweenEquation &easeOutBack;
        static TweenEquation &easeInOutBack;
        static TweenEquation &easeInBounce;
        static TweenEquation &easeOutBounce;
        static TweenEquation &easeInOutBounce;
        static TweenEquation &easeInCirc;
        static TweenEquation &easeOutCirc;
        static TweenEquation &easeInOutCirc;
        static TweenEquation &easeInCubic;
        static TweenEquation &easeOutCubic;
        static TweenEquation &easeInOutCubic;
        static TweenEquation &easeInElastic;
        static TweenEquation &easeOutElastic;
        static TweenEquation &easeInOutElastic;
        static TweenEquation &easeInExpo;
        static TweenEquation &easeOutExpo;
        static TweenEquation &easeInOutExpo;
        static TweenEquation &easeInQuart;
        static TweenEquation &easeOutQuart;
        static TweenEquation &easeInOutQuart;
        static TweenEquation &easeInQuint;
        static TweenEquation &easeOutQuint;
        static TweenEquation &easeInOutQuint;
        static TweenEquation &easeInSine;
        static TweenEquation &easeOutSine;
        static TweenEquation &easeInOutSine;
    };

}

#endif /* defined(__TweenEquations__) */
