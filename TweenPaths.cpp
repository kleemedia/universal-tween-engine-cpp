//
//  TweenPaths.cpp
//
//  This code is derived from Universal Tween Engine
//  Licensed under Apache License 2.0 - http://www.apache.org/licenses/LICENSE-2.0
//

#include "TweenPaths.h"

#include "Linear.h"
#include "CatmullRom.h"

namespace TweenEngine
{
    TweenPath &TweenPaths::linear = *(new Linear());
    TweenPath &TweenPaths::catmullRom = *(new CatmullRom());
}