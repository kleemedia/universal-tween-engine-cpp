//
//  Quart.h
//
//  This code is derived from Universal Tween Engine
//  Licensed under Apache License 2.0 - http://www.apache.org/licenses/LICENSE-2.0
//

#ifndef __Quart__
#define __Quart__

#include "TweenEquation.h"

namespace TweenEngine
{
    class QuartIn : public TweenEquation
    {
        ~QuartIn();
        float compute(float t);
        const char *toString();
    };
    
    class QuartOut : public TweenEquation
    {
        ~QuartOut();
        float compute(float t);
        const char *toString();
    };
    
    class QuartInOut : public TweenEquation
    {
        ~QuartInOut();
        float compute(float t);
        const char *toString();
    };
}

#endif /* defined(__Quart__) */
