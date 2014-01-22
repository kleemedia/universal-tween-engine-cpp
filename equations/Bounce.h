//
//  Bounce.h
//
//  This code is derived from Universal Tween Engine
//  Licensed under Apache License 2.0 - http://www.apache.org/licenses/LICENSE-2.0
//

#ifndef __Bounce__
#define __Bounce__

#include "TweenEquation.h"

namespace TweenEngine
{
    class BounceIn : public TweenEquation
    {
        ~BounceIn();
        float compute(float t);
        const char *toString();
    };
    
    class BounceOut : public TweenEquation
    {
        ~BounceOut();
        float compute(float t);
        const char *toString();
    };
    
    class BounceInOut : public TweenEquation
    {
        ~BounceInOut();
        float compute(float t);
        const char *toString();
    };
}


#endif /* defined(__Bounce__) */
