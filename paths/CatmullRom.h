//
//  CatmullRom.h
//
//  This code is derived from Universal Tween Engine
//  Licensed under Apache License 2.0 - http://www.apache.org/licenses/LICENSE-2.0
//

#ifndef __CatmullRom__
#define __CatmullRom__

#include "TweenPath.h"

namespace TweenEngine
{
    class CatmullRom : public TweenPath
    {
        float compute(float t, float *points, int pointsCnt);
        float catmullRomSpline(float a, float b, float c, float d, float t);
    };
}

#endif /* defined(__CatmullRom__) */
