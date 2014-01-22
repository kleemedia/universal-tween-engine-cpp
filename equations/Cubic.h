//
//  Cubic.h
//
//  This code is derived from Universal Tween Engine
//  Licensed under Apache License 2.0 - http://www.apache.org/licenses/LICENSE-2.0
//

#ifndef __Cubic__
#define __Cubic__

#include "TweenEquation.h"

namespace TweenEngine
{
    class CubicIn : public TweenEquation
    {
        ~CubicIn();
        float compute(float t);
        const char *toString();
    };
    
    class CubicOut : public TweenEquation
    {
        ~CubicOut();
        float compute(float t);
        const char *toString();
    };
    
    class CubicInOut : public TweenEquation
    {
        ~CubicInOut();
        float compute(float t);
        const char *toString();
    };
}

#endif /* defined(__Cubic__) */
