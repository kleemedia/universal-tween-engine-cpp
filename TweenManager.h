//
//  TweenManager.h
//
//  This code is derived from Universal Tween Engine
//  Licensed under Apache License 2.0 - http://www.apache.org/licenses/LICENSE-2.0
//

/**
 * A TweenManager updates all your tweens and timelines at once.
 * Its main interest is that it handles the tween/timeline life-cycles for you,
 * as well as the pooling constraints (if object pooling is enabled).
 * <p/>
 *
 * Just give it a bunch of tweens or timelines and call update() periodically,
 * you don't need to care for anything else! Relax and enjoy your animations.
 *
 * @see Tween
 * @see Timeline
 * @author Aurelien Ribon | http://www.aurelienribon.com/
 */

#ifndef __TweenManager__
#define __TweenManager__

#include <algorithm>
#include <vector>

#include "BaseTween.h"

namespace TweenEngine
{
    class TweenManager
    {
    private:
        std::vector<BaseTween *>objects;

        bool isPaused = false;

    public:
        TweenManager();
        
        static void setAutoRemove(BaseTween &object, bool value);
        static void setAutoStart(BaseTween &object, bool value);
        
        TweenManager &add(BaseTween &object);
        void killAll();
        void ensureCapacity(int minCapacity);
        void pause();
        void resume();
        void update(float delta);
        int size();
        
        // Debug Helpers
        int getRunningTweensCount();
        int getRunningTimelinesCount();
        std::vector<BaseTween *> &getObjects();
    };

}

#endif /* defined(__TweenManager__) */
