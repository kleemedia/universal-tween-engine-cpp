//
//  Back.h
//
//  This code is derived from Universal Tween Engine
//  Licensed under Apache License 2.0 - http://www.apache.org/licenses/LICENSE-2.0
//

#ifndef __Back__
#define __Back__

#include "TweenEquation.h"

namespace TweenEngine
{
    class BackIn : public TweenEquation
    {
        ~BackIn();
        float compute(float t);
        const char *toString();
    };
    
    class BackOut : public TweenEquation
    {
        ~BackOut();
        float compute(float t);
        const char *toString();
    };
    
    class BackInOut : public TweenEquation
    {
        ~BackInOut();
        float compute(float t);
        const char *toString();
    };
}

#endif /* defined(__Back__) */
