//
//  TweenPaths.h
//
//  This code is derived from Universal Tween Engine
//  Licensed under Apache License 2.0 - http://www.apache.org/licenses/LICENSE-2.0
//

#ifndef __TweenPaths__
#define __TweenPaths__

#include "TweenPath.h"

namespace TweenEngine
{
    class TweenPaths
    {
    public:
        static TweenPath &linear;
        static TweenPath &catmullRom;
    };
}

#endif /* defined(__TweenPaths__) */
