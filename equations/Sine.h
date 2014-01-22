//
//  Sine.h
//
//  This code is derived from Universal Tween Engine
//  Licensed under Apache License 2.0 - http://www.apache.org/licenses/LICENSE-2.0
//

#ifndef __Sine__
#define __Sine__

#include "TweenEquation.h"

namespace TweenEngine
{
    class SineIn : public TweenEquation
    {
        ~SineIn();
        float compute(float t);
        const char *toString();
    };
    
    class SineOut : public TweenEquation
    {
        ~SineOut();
        float compute(float t);
        const char *toString();
    };
    
    class SineInOut : public TweenEquation
    {
        ~SineInOut();
        float compute(float t);
        const char *toString();
    };
}

#endif /* defined(__Sine__) */
