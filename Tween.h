//
//  Tween.h
//
//  This code is derived from Universal Tween Engine
//  Licensed under Apache License 2.0 - http://www.apache.org/licenses/LICENSE-2.0
//

#ifndef __Tween__
#define __Tween__

#include <functional>
#include "BaseTween.h"
#include "Pool.h"
#include "TweenEquation.h"
#include "TweenPath.h"
#include "TweenEquations.h"
#include "TweenPaths.h"

using TweenAccessor = std::function<int(int, float *)>;

namespace TweenEngine
{
    class TweenPool;
    class TweenPoolCallback;
    
    class Tween : public BaseTween
    {
        friend class TweenPoolCallback;
        
    private:
        static int combinedAttrsLimit;
        static int waypointsLimit;
        
        // Main
		TweenAccessor accessor;
		int targetId;
		TweenEquation *equation;
        TweenPath *pathAlgorithm;

        // General
        bool isFrom;
        bool isRelative;
        int combinedAttrsCnt;
        int waypointsCnt;

        // Values
        float* startValues;
        float* targetValues;
        float* waypoints;
        
        // Buffers
        float *accessorBuffer;
        int accessorBufferSize;
        float *pathBuffer;
        int pathBufferSize;

        static TweenPool &pool;

        void setup(int target, float duration, TweenAccessor accessor);
        
    protected:
        virtual void reset();
        virtual void forceStartValues();
        virtual void forceEndValues();
        virtual bool containsTarget(int targetId);
        virtual void initializeOverride();
        virtual void updateOverride(int step, int lastStep, bool isIterationStep, float delta);
        
    public:
        static const int ACCESSOR_READ = 0;
        static const int ACCESSOR_WRITE = 1;

        static void setCombinedAttributesLimit(int limit);
        static void setWaypointsLimit(int limit);
        static const char *getVersion();
        
        static size_t getPoolSize();
        static void ensurePoolCapacity(int minCapacity);
      
        static Tween &to(int targetId, float duration, TweenAccessor accessor);
        static Tween &from(int targetId, float duration, TweenAccessor accessor);
        static Tween &set(int targetId, TweenAccessor accessor);
        static Tween &call(TweenCallback &callback);
        static Tween &mark();
        
        Tween();
        ~Tween();

        virtual int getTweenCount();
        virtual int getTimelineCount();
        
        virtual Tween &build();
        virtual void free();
        
        Tween &ease(TweenEquation &easeEquation);
        Tween &target(float targetValue);
        Tween &target(float targetValue1, float targetValue2);
        Tween &target(float targetValue1, float targetValue2, float targetValue3);
        Tween &target(float *targetValues, int len);
        Tween &targetRelative(float targetValue);
        Tween &targetRelative(float targetValue1, float targetValue2);
        Tween &targetRelative(float targetValue1, float targetValue2, float targetValue3);
        Tween &targetRelative(float *targetValues, int len);
        Tween &waypoint(float targetValue);
        Tween &waypoint(float targetValue1, float targetValue2);
        Tween &waypoint(float targetValue1, float targetValue2, float targetValue3);
        Tween &waypoint(float *targetValues, int len);
        Tween &path(TweenPath &path);
        int getType();
        TweenEquation *getEasing();
        float *getTargetValues();
        int getCombinedAttributesCount();

        
    };
}

#endif /* defined(__Tween__) */
