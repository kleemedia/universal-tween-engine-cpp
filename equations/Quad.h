//
//  Quad.h
//
//  This code is derived from Universal Tween Engine
//  Licensed under Apache License 2.0 - http://www.apache.org/licenses/LICENSE-2.0
//

#ifndef __Quad__
#define __Quad__

#include "TweenEquation.h"

namespace TweenEngine
{
    class QuadIn : public TweenEquation
    {
        ~QuadIn();
        float compute(float t);
        const char *toString();
    };

    class QuadOut : public TweenEquation
    {
        ~QuadOut();
        float compute(float t);
        const char *toString();
    };

    class QuadInOut : public TweenEquation
    {
        ~QuadInOut();
        float compute(float t);
        const char *toString();
    };
}

#endif /* defined(__Quad__) */
