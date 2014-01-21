//
//  BaseTween.h
//
//  This code is derived from Universal Tween Engine
//  Licensed under Apache License 2.0 - http://www.apache.org/licenses/LICENSE-2.0
//

/**
 * BaseTween is the base class of Tween and Timeline. It defines the
 * iteration engine used to play animations for any number of times, and in
 * any direction, at any speed.
 * <p/>
 *
 * It is responsible for calling the different callbacks at the right moments,
 * and for making sure that every callbacks are triggered, even if the update
 * engine gets a big delta time at once.
 *
 * @see Tween
 * @see Timeline
 * @author Aurelien Ribon | http://www.aurelienribon.com/
 */

#ifndef __BaseTween__
#define __BaseTween__

#include "TweenCallback.h"

namespace TweenEngine
{
    class TweenManager;
    
    class BaseTween
    {
    private:
        // General
        int step;
        int repeatCnt;
        bool isIterationStep;
        bool isYoyoFlag;
        
        // Timings
        float repeatDelay;
        float currentTime;
        float deltaTime;
        bool isStartedFlag;     // true when the object is started
        bool isInitializedFlag; // true after the delay
        bool isFinishedFlag;    // true when all repetitions are done
        bool isKilledFlag;      // true if kill() was called
        bool isPausedFlag;      // true if pause() was called
        
        // Misc
        TweenCallback *callback;
        int callbackTriggers;
        void *userData;

        // Update
        void initialize();
        void testRelaunch();
        void updateStep();
        void testCompletion();
        
    protected:
        // Timings
        float delayStart;
        float duration;

        virtual void reset();
        virtual void forceStartValues() = 0;
        virtual void forceEndValues() = 0;
        virtual void initializeOverride();
        virtual void updateOverride(int step, int lastStep, bool isIterationStep, float delta);
        virtual void forceToStart();
        virtual void forceToEnd(float time);
        
        void callCallback(int type);
        bool isReverse(int step);
        bool isValid(int step);

    public:
        virtual ~BaseTween() {}

        virtual int getTweenCount() = 0;
        virtual int getTimelineCount() = 0;

        // Package access
        bool isAutoRemoveEnabled;
        bool isAutoStartEnabled;

        virtual BaseTween &build();
        BaseTween &start();
        BaseTween &start(TweenManager &manager);
        BaseTween &delay(float delay);
        void kill();
        virtual void free();
        void pause();
        void resume();
        BaseTween &repeat(int count, float delay);
        BaseTween &repeatYoyo(int count, float delay);
        BaseTween &setCallback(TweenCallback *callback);
        BaseTween &setCallbackTriggers(int flags);
        BaseTween &setUserData(void *data);
        
        // Getters
        float getDelay();
        float getDuration();
        int getRepeatCount();
        float getRepeatDelay();
        float getFullDuration();
        void *getUserData();
        int getStep();
        float getCurrentTime();
        bool isStarted();
        bool isInitialized();
        bool isFinished();
        bool isYoyo();
        bool isPaused();
        
        // Update
        void update(float delta);

    };

}

#endif /* defined(__BaseTween__) */









































