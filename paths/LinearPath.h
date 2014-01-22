//
//  Linear.h
//
//  This code is derived from Universal Tween Engine
//  Licensed under Apache License 2.0 - http://www.apache.org/licenses/LICENSE-2.0
//

#ifndef __LinearPath__
#define __LinearPath__

#include "TweenPath.h"

namespace TweenEngine
{
    class LinearPath : public TweenPath
    {
        float compute(float t, float *points, int pointsCnt);
    };
}

#endif /* defined(__LinearPath__) */
