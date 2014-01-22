//
//  Expo.h
//
//  This code is derived from Universal Tween Engine
//  Licensed under Apache License 2.0 - http://www.apache.org/licenses/LICENSE-2.0
//

#ifndef __Expo__
#define __Expo__

#include "TweenEquation.h"

namespace TweenEngine
{
    class ExpoIn : public TweenEquation
    {
        ~ExpoIn();
        float compute(float t);
        const char *toString();
    };
    
    class ExpoOut : public TweenEquation
    {
        ~ExpoOut();
        float compute(float t);
        const char *toString();
    };
    
    class ExpoInOut : public TweenEquation
    {
        ~ExpoInOut();
        float compute(float t);
        const char *toString();
    };
}

#endif /* defined(__Expo__) */
