//
//  Linear.h
//
//  This code is derived from Universal Tween Engine
//  Licensed under Apache License 2.0 - http://www.apache.org/licenses/LICENSE-2.0
//

#ifndef __Linear__
#define __Linear__

#include "TweenEquation.h"

namespace TweenEngine
{
    class LinearInOut : public TweenEquation
    {
        ~LinearInOut();
        float compute(float t);
        const char *toString();
    };
}


#endif /* defined(__Linear__) */
