//
//  Linear.cpp
//
//  This code is derived from Universal Tween Engine
//  Licensed under Apache License 2.0 - http://www.apache.org/licenses/LICENSE-2.0
//

#include <math.h>
#include "LinearPath.h"

namespace TweenEngine
{
    float LinearPath::compute(float t, float *points, int pointsCnt)
    {
        int segment = (int) floor((pointsCnt-1) * t);
		segment = segment > 0 ? segment : 0;
		segment = segment < (pointsCnt-2) ? segment : pointsCnt-2;
        
		t = t * (pointsCnt-1) - segment;
        
		return points[segment] + t * (points[segment+1] - points[segment]);
    }
}