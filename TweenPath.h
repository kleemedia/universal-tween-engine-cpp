//
//  TweenPath.h
//
//  This code is derived from Universal Tween Engine
//  Licensed under Apache License 2.0 - http://www.apache.org/licenses/LICENSE-2.0
//

/**
 * Base class for every paths. You can create your own paths and directly use
 * them in the Tween engine by inheriting from this class.
 *
 * @author Aurelien Ribon | http://www.aurelienribon.com/
 */

#ifndef __TweenPath__
#define __TweenPath__

namespace TweenEngine
{
    class TweenPath
    {
    public:
        /**
         * Computes the next value of the interpolation, based on its waypoints and
         * the current progress.
         *
         * @param t The progress of the interpolation, between 0 and 1. May be out
         * of these bounds if the easing equation involves some kind of rebounds.
         * @param points The waypoints of the tween, from start to target values.
         * @param pointsCnt The number of valid points in the array.
         * @return The next value of the interpolation.
         */
        virtual float compute(float t, float *points, int pointsCnt) = 0;
    };
}

#endif /* defined(__TweenPath__) */
