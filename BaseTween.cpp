//
//  BaseTween.cpp
//
//  This code is derived from Universal Tween Engine
//  Licensed under Apache License 2.0 - http://www.apache.org/licenses/LICENSE-2.0
//

//#define NDEBUG
#include <assert.h>

#include "BaseTween.h"

#include "TweenManager.h"

namespace TweenEngine
{
    void BaseTween::reset()
    {
        step = -2;
		repeatCnt = 0;
		isIterationStep = isYoyoFlag = false;
        
		delayStart = duration = repeatDelay = currentTime = deltaTime = 0;
		isStartedFlag = isInitializedFlag = isFinishedFlag = isKilledFlag = isPausedFlag = false;
        
		callback = NULL;
		callbackTriggers = TweenCallback::COMPLETE;
		userData = NULL;
        
		isAutoRemoveEnabled = isAutoStartEnabled = true;
    }
    
    //  API
    
    /**
	 * Builds and validates the object. Only needed if you want to finalize a
	 * tween or timeline without starting it, since a call to ".start()" also
	 * calls this method.
	 *
	 * @return The current object, for chaining instructions.
	 */
    BaseTween &BaseTween::build()
    {
		return *this;
	}
    
	/**
	 * Starts or restarts the object unmanaged. You will need to take care of
	 * its life-cycle. If you want the tween to be managed for you, use a
	 * {@link TweenManager}.
	 *
	 * @return The current object, for chaining instructions.
	 */
	BaseTween &BaseTween::start()
    {
		build();
		currentTime = 0;
		isStartedFlag = true;
		return *this;
	}

    /**
	 * Convenience method to add an object to a manager. Its life-cycle will be
	 * handled for you. Relax and enjoy the animation.
	 *
	 * @return The current object, for chaining instructions.
	 */
	BaseTween &BaseTween::start(TweenManager &manager) {
		manager.add(*this);
		return *this;
	}

    /**
	 * Adds a delay to the tween or timeline.
	 *
	 * @param delay A duration.
	 * @return The current object, for chaining instructions.
	 */
	BaseTween &BaseTween::delay(float delay)
    {
		this->delayStart += delay;
		return *this;
	}
    
	/**
	 * Kills the tween or timeline. If you are using a TweenManager, this object
	 * will be removed automatically.
	 */
	void BaseTween::kill()
    {
		isKilledFlag = true;
	}
    
	/**
	 * Stops and resets the tween or timeline, and sends it to its pool, for
     +	 * later reuse. Note that if you use a {@link TweenManager}, this method
     +	 * is automatically called once the animation is finished.
	 */
	void BaseTween::free()
    {
	}
    
	/**
	 * Pauses the tween or timeline. Further update calls won't have any effect.
	 */
	void BaseTween::pause()
    {
		isPausedFlag = true;
	}
    
	/**
	 * Resumes the tween or timeline. Has no effect is it was no already paused.
	 */
	void BaseTween::resume()
    {
		isPausedFlag = false;
	}
    
	/**
	 * Repeats the tween or timeline for a given number of times.
	 * @param count The number of repetitions. For infinite repetition,
	 * use Tween.INFINITY, or a negative number.
	 *
	 * @param delay A delay between each iteration.
	 * @return The current tween or timeline, for chaining instructions.
	 */
	BaseTween &BaseTween::repeat(int count, float delay)
    {
		if (isStartedFlag)
        {
            //throw new RuntimeException("You can't change the repetitions of a tween or timeline once it is started");
        }
        else
        {
            repeatCnt = count;
            repeatDelay = delay >= 0 ? delay : 0;
            isYoyoFlag = false;
        }
		return *this;
	}
    
	/**
	 * Repeats the tween or timeline for a given number of times.
	 * Every two iterations, it will be played backwards.
	 *
	 * @param count The number of repetitions. For infinite repetition,
	 * use Tween.INFINITY, or '-1'.
	 * @param delay A delay before each repetition.
	 * @return The current tween or timeline, for chaining instructions.
	 */
	BaseTween &BaseTween::repeatYoyo(int count, float delay)
    {
		if (isStartedFlag)
        {
            //throw new RuntimeException("You can't change the repetitions of a tween or timeline once it is started");
        }
        else
        {
            repeatCnt = count;
            repeatDelay = delay >= 0 ? delay : 0;
            isYoyoFlag = true;
        }
		return *this;
	}
    
	/**
	 * Sets the callback. By default, it will be fired at the completion of the
	 * tween or timeline (event COMPLETE). If you want to change this behavior
	 * and add more triggers, use the {@link setCallbackTriggers()} method.
	 *
	 * @see TweenCallback
	 */
	BaseTween &BaseTween::setCallback(TweenCallback *callback)
    {
		this->callback = callback;
		return *this;
	}
    
	/**
	 * Changes the triggers of the callback. The available triggers, listed as
	 * members of the {@link TweenCallback} interface, are:
	 * <p/>
	 *
	 * <b>BEGIN</b>: right after the delay (if any)<br/>
	 * <b>START</b>: at each iteration beginning<br/>
	 * <b>END</b>: at each iteration ending, before the repeat delay<br/>
	 * <b>COMPLETE</b>: at last END event<br/>
	 * <b>BACK_BEGIN</b>: at the beginning of the first backward iteration<br/>
	 * <b>BACK_START</b>: at each backward iteration beginning, after the repeat delay<br/>
	 * <b>BACK_END</b>: at each backward iteration ending<br/>
	 * <b>BACK_COMPLETE</b>: at last BACK_END event
	 * <p/>
	 *
	 * <pre> {@code
	 * forward :      BEGIN                                   COMPLETE
	 * forward :      START    END      START    END      START    END
	 * |--------------[XXXXXXXXXX]------[XXXXXXXXXX]------[XXXXXXXXXX]
	 * backward:      bEND  bSTART      bEND  bSTART      bEND  bSTART
	 * backward:      bCOMPLETE                                 bBEGIN
	 * }</pre>
	 *
	 * @param flags one or more triggers, separated by the '|' operator.
	 * @see TweenCallback
	 */
	BaseTween &BaseTween::setCallbackTriggers(int flags)
    {
		this->callbackTriggers = flags;
		return *this;
	}
    
	/**
	 * Attaches an object to this tween or timeline. It can be useful in order
	 * to retrieve some data from a TweenCallback.
	 *
	 * @param data Any kind of object.
	 * @return The current tween or timeline, for chaining instructions.
	 */
	BaseTween &BaseTween::setUserData(void *data)
    {
		userData = data;
		return *this;
	}
    
    // -------------------------------------------------------------------------
	// Getters
	// -------------------------------------------------------------------------
    
	/**
	 * Gets the delay of the tween or timeline. Nothing will happen before
	 * this delay.
	 */
	float BaseTween::getDelay() { return delayStart; }
    
	/**
	 * Gets the duration of a single iteration.
	 */
	float BaseTween::getDuration() { return duration; }
    
	/**
	 * Gets the number of iterations that will be played.
	 */
    int BaseTween::getRepeatCount() { return repeatCnt; }
    
	/**
	 * Gets the delay occuring between two iterations.
	 */
	 float BaseTween::getRepeatDelay() { return repeatDelay; }
    
	/**
	 * Returns the complete duration, including initial delay and repetitions.
	 * The formula is as follows:
	 * <pre>
	 * fullDuration = delay + duration + (repeatDelay + duration) * repeatCnt
	 * </pre>
	 */
	float BaseTween::getFullDuration()
    {
		if (repeatCnt < 0) return -1;
		return delayStart + duration + (repeatDelay + duration) * repeatCnt;
	}
    
	/**
	 * Gets the attached data, or null if none.
	 */
	void *BaseTween::getUserData() { return userData; }
    
	/**
	 * Gets the id of the current step. Values are as follows:<br/>
	 * <ul>
	 * <li>even numbers mean that an iteration is playing,<br/>
	 * <li>odd numbers mean that we are between two iterations,<br/>
	 * <li>-2 means that the initial delay has not ended,<br/>
	 * <li>-1 means that we are before the first iteration,<br/>
	 * <li>repeatCount*2 + 1 means that we are after the last iteration
	 */
	int BaseTween::getStep() { return step; }
    
	/**
	 * Gets the local time.
	 */
	float BaseTween::getCurrentTime() { return currentTime; }
    
	/**
	 * Returns true if the tween or timeline has been started.
	 */
	bool BaseTween::isStarted() { return isStartedFlag; }
    
	/**
	 * Returns true if the tween or timeline has been initialized. Starting
	 * values for tweens are stored at initialization time. This initialization
	 * takes place right after the initial delay, if any.
	 */
	bool BaseTween::isInitialized() { return isInitializedFlag; }
    
	/**
	 * Returns true if the tween is finished (i.e. if the tween has reached
	 * its end or has been killed). If you don't use a TweenManager, you may
	 * want to call {@link free()} to reuse the object later.
	 */
	bool BaseTween::isFinished() { return isFinishedFlag || isKilledFlag; }
    
	/**
	 * Returns true if the iterations are played as yoyo. Yoyo means that
	 * every two iterations, the animation will be played backwards.
	 */
	bool BaseTween::isYoyo() { return isYoyoFlag; }
    
	/**
	 * Returns true if the tween or timeline is currently paused.
	 */
	bool BaseTween::isPaused() { return isPausedFlag; }

    void BaseTween::initializeOverride() {}
    
    void BaseTween::updateOverride(int step, int lastStep, bool isIterationStep, float delta) {}
    
    void BaseTween::forceToStart()
    {
        currentTime = -delayStart;
        step = -1;
        isIterationStep = false;
        if (isReverse(0)) forceEndValues();
        else forceStartValues();
    }
    
    void BaseTween::forceToEnd(float time)
    {
        currentTime = time - getFullDuration();
        step = repeatCnt*2 + 1;
        isIterationStep = false;
        if (isReverse(repeatCnt*2)) forceStartValues();
        else forceEndValues();
    }
    
    void BaseTween::callCallback(int type)
    {
        if (callback != NULL && (callbackTriggers & type) > 0) callback->onEvent(type, this);
    }
    
    bool BaseTween::isReverse(int step)
    {
        return isYoyoFlag && abs(step%4) == 2;
    }
    
    bool BaseTween::isValid(int step)
    {
        return (step >= 0 && step <= repeatCnt*2) || repeatCnt < 0;
    }
    
    // -------------------------------------------------------------------------
	// Update engine
	// -------------------------------------------------------------------------
    
	/**
	 * Updates the tween or timeline state. <b>You may want to use a
	 * TweenManager to update objects for you.</b>
	 *
	 * Slow motion, fast motion and backward play can be easily achieved by
	 * tweaking this delta time. Multiply it by -1 to play the animation
	 * backward, or by 0.5 to play it twice slower than its normal speed.
	 *
	 * @param delta A delta time between now and the last call.
	 */
	void BaseTween::update(float delta)
    {
		if (!isStartedFlag || isPausedFlag || isKilledFlag) return;
        
		deltaTime = delta;
        
		if (!isInitializedFlag) initialize();
        
		if (isInitializedFlag)
        {
			testRelaunch();
			updateStep();
			testCompletion();
		}
        
		currentTime += deltaTime;
		deltaTime = 0;
	}

    void BaseTween::initialize() {
        if (currentTime+deltaTime >= delayStart)
        {
            initializeOverride();
            isInitializedFlag = true;
            isIterationStep = true;
            step = 0;
            deltaTime -= delayStart-currentTime;
            currentTime = 0;
            callCallback(TweenCallback::BEGIN);
            callCallback(TweenCallback::START);
        }
    }
    
    void BaseTween::testRelaunch()
    {
        if (!isIterationStep && repeatCnt >= 0 && step < 0 && currentTime+deltaTime >= 0)
        {
            assert(step == -1);
            isIterationStep = true;
            step = 0;
            float delta = 0-currentTime;
            deltaTime -= delta;
            currentTime = 0;
            callCallback(TweenCallback::BEGIN);
            callCallback(TweenCallback::START);
            updateOverride(step, step-1, isIterationStep, delta);
            
        }
        else if (!isIterationStep && repeatCnt >= 0 && step > repeatCnt*2 && currentTime+deltaTime < 0)
        {
            assert(step == repeatCnt*2 + 1);
            isIterationStep = true;
            step = repeatCnt*2;
            float delta = 0-currentTime;
            deltaTime -= delta;
            currentTime = duration;
            callCallback(TweenCallback::BACK_BEGIN);
            callCallback(TweenCallback::BACK_START);
            updateOverride(step, step+1, isIterationStep, delta);
        }
    }
    
    void BaseTween::updateStep()
    {
        while (isValid(step))
        {
            if (!isIterationStep && currentTime+deltaTime <= 0)
            {
                isIterationStep = true;
                step -= 1;
                
                float delta = 0-currentTime;
                deltaTime -= delta;
                currentTime = duration;
                
                if (isReverse(step)) forceStartValues();
                else forceEndValues();
                callCallback(TweenCallback::BACK_START);
                updateOverride(step, step+1, isIterationStep, delta);
                
            }
            else if (!isIterationStep && currentTime+deltaTime >= repeatDelay)
            {
                isIterationStep = true;
                step += 1;
                
                float delta = repeatDelay-currentTime;
                deltaTime -= delta;
                currentTime = 0;
                
                if (isReverse(step)) forceEndValues(); else forceStartValues();
                callCallback(TweenCallback::START);
                updateOverride(step, step-1, isIterationStep, delta);
                
            }
            else if (isIterationStep && currentTime+deltaTime < 0)
            {
                isIterationStep = false;
                step -= 1;
                
                float delta = 0-currentTime;
                deltaTime -= delta;
                currentTime = 0;
                
                updateOverride(step, step+1, isIterationStep, delta);
                callCallback(TweenCallback::BACK_END);
                
                if (step < 0 && repeatCnt >= 0) callCallback(TweenCallback::BACK_COMPLETE);
                else currentTime = repeatDelay;
                
            }
            else if (isIterationStep && currentTime+deltaTime > duration)
            {
                isIterationStep = false;
                step += 1;
                
                float delta = duration-currentTime;
                deltaTime -= delta;
                currentTime = duration;
                
                updateOverride(step, step-1, isIterationStep, delta);
                callCallback(TweenCallback::END);
                
                if (step > repeatCnt*2 && repeatCnt >= 0) callCallback(TweenCallback::COMPLETE);
                currentTime = 0;
                
            }
            else if (isIterationStep)
            {
                float delta = deltaTime;
                deltaTime -= delta;
                currentTime += delta;
                updateOverride(step, step, isIterationStep, delta);
                break;
                
            }
            else
            {
                float delta = deltaTime;
                deltaTime -= delta;
                currentTime += delta;
                break;
            }
        }
    }
    
    void BaseTween::testCompletion()
    {
        isFinishedFlag = repeatCnt >= 0 && (step > repeatCnt*2 || step < 0);
    }


}