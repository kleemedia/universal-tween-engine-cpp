//
//  Quint.h
//
//  This code is derived from Universal Tween Engine
//  Licensed under Apache License 2.0 - http://www.apache.org/licenses/LICENSE-2.0
//

#ifndef __Quint__
#define __Quint__

#include "TweenEquation.h"

namespace TweenEngine
{
    class QuintIn : public TweenEquation
    {
        ~QuintIn();
        float compute(float t);
        const char *toString();
    };
    
    class QuintOut : public TweenEquation
    {
        ~QuintOut();
        float compute(float t);
        const char *toString();
    };
    
    class QuintInOut : public TweenEquation
    {
        ~QuintInOut();
        float compute(float t);
        const char *toString();
    };
}

#endif /* defined(__Quint__) */
