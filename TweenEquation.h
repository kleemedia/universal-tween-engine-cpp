//
//  TweenEquation.h
//
//  This code is derived from Universal Tween Engine
//  Licensed under Apache License 2.0 - http://www.apache.org/licenses/LICENSE-2.0
//

/**
 * Base class for every easing equation. You can create your own equations
 * and directly use them in the Tween engine by inheriting from this class.
 *
 * @see Tween
 * @author Aurelien Ribon | http://www.aurelienribon.com/
 */

#ifndef __TweenEquation__
#define __TweenEquation__

//#include <string.h>

namespace TweenEngine
{
    class TweenEquation
    {
    public:
        /**
         * Computes the next value of the interpolation.
         *
         * @param t The current time, between 0 and 1.
         * @return The current value.
         */
        virtual float compute(float t) = 0;

        virtual const char *toString() = 0;

        /**
         * Returns true if the given string is the name of this equation (the name
         * is returned in the toString() method, don't forget to override it).
         * This method is usually used to save/load a tween to/from a text file.
         */
        //bool isValueOf(const char *str) { return !strcmp(str, toString()); };
        
    };
}

#endif /* defined(__TweenEquation__) */
