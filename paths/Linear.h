//
//  Linear.h
//
//  This code is derived from Universal Tween Engine
//  Licensed under Apache License 2.0 - http://www.apache.org/licenses/LICENSE-2.0
//

#ifndef __Linear__
#define __Linear__

#include "TweenPath.h"

namespace TweenEngine
{
    class Linear : public TweenPath
    {
        float compute(float t, float *points, int pointsCnt);
    };
}

#endif /* defined(__Linear__) */
