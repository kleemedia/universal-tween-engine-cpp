//
//  Circ.h
//
//  This code is derived from Universal Tween Engine
//  Licensed under Apache License 2.0 - http://www.apache.org/licenses/LICENSE-2.0
//

#ifndef __Circ__
#define __Circ__

#include "TweenEquation.h"

namespace TweenEngine
{
    class CircIn : public TweenEquation
    {
        ~CircIn();
        float compute(float t);
        const char *toString();
    };
    
    class CircOut : public TweenEquation
    {
        ~CircOut();
        float compute(float t);
        const char *toString();
    };
    
    class CircInOut : public TweenEquation
    {
        ~CircInOut();
        float compute(float t);
        const char *toString();
    };
}

#endif /* defined(__Circ__) */
