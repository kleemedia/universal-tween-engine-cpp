//
//  Tween.cpp
//
//  This code is derived from Universal Tween Engine
//  Licensed under Apache License 2.0 - http://www.apache.org/licenses/LICENSE-2.0
//

/**
 * Core class of the Tween Engine. A Tween is basically an interpolation
 * between two values of an object attribute. However, the main interest of a
 * Tween is that you can apply an easing formula on this interpolation, in
 * order to smooth the transitions or to achieve cool effects like springs or
 * bounces.
 * <p/>
 *
 * The Universal Tween Engine is called "universal" because it is able to apply
 * interpolations on every attribute from every possible object. Therefore,
 * every object in your application can be animated with cool effects: it does
 * not matter if your application is a game, a desktop interface or even a
 * console program! If it makes sense to animate something, then it can be
 * animated through this engine.
 * <p/>
 *
 * This class contains many static factory methods to create and instantiate
 * new interpolations easily. The common way to create a Tween is by using one
 * of these factories:
 * <p/>
 *
 * - Tween.to(...)<br/>
 * - Tween.from(...)<br/>
 * - Tween.set(...)<br/>
 * - Tween.call(...)
 * <p/>
 *
 * <h2>Example - firing a Tween</h2>
 *
 * The following example will move the target horizontal position from its
 * current value to x=200 and y=300, during 500ms, but only after a delay of
 * 1000ms. The animation will also be repeated 2 times (the starting position
 * is registered at the end of the delay, so the animation will automatically
 * restart from this registered position).
 * <p/>
 *
 * <pre> {@code
 * Tween.to(myObject, POSITION_XY, 0.5f)
 *      .target(200, 300)
 *      .ease(Quad.INOUT)
 *      .delay(1.0f)
 *      .repeat(2, 0.2f)
 *      .start(myManager);
 * }</pre>
 *
 * Tween life-cycles can be automatically managed for you, thanks to the
 * {@link TweenManager} class. If you choose to manage your tween when you start
 * it, then you don't need to care about it anymore. <b>Tweens are
 * <i>fire-and-forget</i>: don't think about them anymore once you started
 * them (if they are managed of course).</b>
 * <p/>
 *
 * You need to periodicaly update the tween engine, in order to compute the new
 * values. If your tweens are managed, only update the manager; else you need
 * to call {@link #update()} on your tweens periodically.
 * <p/>
 *
 * <h2>Example - setting up the engine</h2>
 *
 * The engine cannot directly change your objects attributes, since it doesn't
 * know them. Therefore, you need to tell him how to get and set the different
 * attributes of your objects: <b>you need to implement the {@link
 * TweenAccessor} interface for each object class you will animate</b>. Once
 * done, don't forget to register these implementations, using the static method
 * {@link registerAccessor()}, when you start your application.
 *
 * @see TweenAccessor
 * @see TweenManager
 * @see TweenEquation
 * @see Timeline
 * @author Aurelien Ribon | http://www.aurelienribon.com/
 */

//#define NDEBUG
#include <assert.h>
#include <Block.h>

#include "Tween.h"
#include "TweenPool.h"

namespace TweenEngine
{
    int Tween::combinedAttrsLimit = 3;
    int Tween::waypointsLimit = 0;
    
	/**
	 * Changes the limit for combined attributes. Defaults to 3 to reduce
	 * memory footprint.
	 */
	void Tween::setCombinedAttributesLimit(int limit) { Tween::combinedAttrsLimit = limit; }
    
	/**
	 * Changes the limit of allowed waypoints for each tween. Defaults to 0 to
	 * reduce memory footprint.
	 */
	void Tween::setWaypointsLimit(int limit) { Tween::waypointsLimit = limit; }
    
	/**
	 * Gets the version number of the library.
	 */
	const char *Tween::getVersion() { return "6.3.3"; }
   
	/**
	 * Used for debug purpose. Gets the current number of objects that are
	 * waiting in the Tween pool.
	 */
	int Tween::getPoolSize() { return pool.size(); }
    
	/**
	 * Increases the minimum capacity of the pool. Capacity defaults to 20.
	 */
	void Tween::ensurePoolCapacity(int minCapacity) { pool.ensureCapacity(minCapacity); }

    TweenPool &Tween::pool = *(new TweenPool());
    
	// -------------------------------------------------------------------------
	// Static -- factories
	// -------------------------------------------------------------------------
    
	/**
	 * Factory creating a new standard interpolation. This is the most common
	 * type of interpolation. The starting values are retrieved automatically
	 * after the delay (if any).
	 * <br/><br/>
	 *
	 * <b>You need to set the target values of the interpolation by using one
	 * of the target() methods</b>. The interpolation will run from the
	 * starting values to these target values.
	 * <br/><br/>
	 *
	 * The common use of Tweens is "fire-and-forget": you do not need to care
	 * for tweens once you added them to a TweenManager, they will be updated
	 * automatically, and cleaned once finished. Common call:
	 * <br/><br/>
	 *
	 * <pre> {@code
	 * Tween.to(myObject, POSITION, 1.0f)
	 *      .target(50, 70)
	 *      .ease(Quad.INOUT)
	 *      .start(myManager);
	 * }</pre>
	 *
	 * Several options such as delay, repetitions and callbacks can be added to
	 * the tween.
	 *
	 * @param target The target object of the interpolation.
	 * @param tweenType The desired type of interpolation.
	 * @param duration The duration of the interpolation, in milliseconds.
	 * @return The generated Tween.
	 */
	Tween &Tween::to(Accessor accessor, float duration)
    {
		Tween &tween = *(pool.get());
		tween.setup(accessor, duration);
        tween.ease(TweenEquations::easeInOutQuad);
		tween.path(TweenPaths::catmullRom);
		return tween;
	}

    /**
	 * Factory creating a new reversed interpolation. The ending values are
	 * retrieved automatically after the delay (if any).
	 * <br/><br/>
	 *
	 * <b>You need to set the starting values of the interpolation by using one
	 * of the target() methods</b>. The interpolation will run from the
	 * starting values to these target values.
	 * <br/><br/>
	 *
	 * The common use of Tweens is "fire-and-forget": you do not need to care
	 * for tweens once you added them to a TweenManager, they will be updated
	 * automatically, and cleaned once finished. Common call:
	 * <br/><br/>
	 *
	 * <pre> {@code
	 * Tween.from(myObject, POSITION, 1.0f)
	 *      .target(0, 0)
	 *      .ease(Quad.INOUT)
	 *      .start(myManager);
	 * }</pre>
	 *
	 * Several options such as delay, repetitions and callbacks can be added to
	 * the tween.
	 *
	 * @param target The target object of the interpolation.
	 * @param tweenType The desired type of interpolation.
	 * @param duration The duration of the interpolation, in milliseconds.
	 * @return The generated Tween.
	 */
	Tween &Tween::from(Accessor accessor, float duration)
    {
		Tween &tween = *(pool.get());
		tween.setup(accessor, duration);
        tween.ease(TweenEquations::easeInOutQuad);
		tween.path(TweenPaths::catmullRom);
		tween.isFrom = true;
		return tween;
	}

    /**
	 * Factory creating a new instantaneous interpolation (thus this is not
	 * really an interpolation).
	 * <br/><br/>
	 *
	 * <b>You need to set the target values of the interpolation by using one
	 * of the target() methods</b>. The interpolation will set the target
	 * attribute to these values after the delay (if any).
	 * <br/><br/>
	 *
	 * The common use of Tweens is "fire-and-forget": you do not need to care
	 * for tweens once you added them to a TweenManager, they will be updated
	 * automatically, and cleaned once finished. Common call:
	 * <br/><br/>
	 *
	 * <pre> {@code
	 * Tween.set(myObject, POSITION)
	 *      .target(50, 70)
	 *      .delay(1.0f)
	 *      .start(myManager);
	 * }</pre>
	 *
	 * Several options such as delay, repetitions and callbacks can be added to
	 * the tween.
	 *
	 * @param target The target object of the interpolation.
	 * @param tweenType The desired type of interpolation.
	 * @return The generated Tween.
	 */
	Tween &Tween::set(Accessor accessor)
    {
		Tween &tween = *(pool.get());
		tween.setup(accessor, 0);
        tween.ease(TweenEquations::easeInOutQuad);
		return tween;
	}

    /**
	 * Factory creating a new timer. The given callback will be triggered on
	 * each iteration start, after the delay.
	 * <br/><br/>
	 *
	 * The common use of Tweens is "fire-and-forget": you do not need to care
	 * for tweens once you added them to a TweenManager, they will be updated
	 * automatically, and cleaned once finished. Common call:
	 * <br/><br/>
	 *
	 * <pre> {@code
	 * Tween.call(myCallback)
	 *      .delay(1.0f)
	 *      .repeat(10, 1000)
	 *      .start(myManager);
	 * }</pre>
	 *
	 * @param callback The callback that will be triggered on each iteration
	 * start.
	 * @return The generated Tween.
	 * @see TweenCallback
	 */
	Tween &Tween::call(TweenCallback &callback)
    {
		Tween &tween = *(pool.get());
		tween.setup(NULL, 0);
		tween.setCallback(&callback);
		tween.setCallbackTriggers(TweenCallback::START);
		return tween;
	}
    
	/**
	 * Convenience method to create an empty tween. Such object is only useful
	 * when placed inside animation sequences (see {@link Timeline}), in which
	 * it may act as a beacon, so you can set a callback on it in order to
	 * trigger some action at the right moment.
	 *
	 * @return The generated Tween.
	 * @see Timeline
	 */
	Tween &Tween::mark()
    {
		Tween &tween = *(pool.get());
		tween.setup(NULL, 0);
		return tween;
	}
    
    // -------------------------------------------------------------------------
	// Setup
	// -------------------------------------------------------------------------

    Tween::Tween()
    {
        startValues = new float[combinedAttrsLimit];
        targetValues = new float[combinedAttrsLimit];
        waypoints = new float[waypointsLimit*combinedAttrsLimit];
        accessorBuffer = new float[combinedAttrsLimit];
        accessorBufferSize = combinedAttrsLimit;
        pathBuffer = new float[(2+waypointsLimit)*combinedAttrsLimit];
        pathBufferSize = (2+waypointsLimit)*combinedAttrsLimit;
        accessor = NULL;
    }
    
    Tween::~Tween()
    {
        delete startValues;
        delete targetValues;
        delete waypoints;
        delete accessorBuffer;
        delete pathBuffer;
        if (accessor != NULL) Block_release(accessor);
    }

    void Tween::reset()
    {
        BaseTween::reset();
        
        equation = NULL;
        pathAlgorithm = NULL;
        isFrom = isRelative = false;
		combinedAttrsCnt = waypointsCnt = 0;
        
		if (accessorBufferSize != combinedAttrsLimit) {
			accessorBuffer = new float[combinedAttrsLimit];
		}
        
		if (pathBufferSize != (2+waypointsLimit)*combinedAttrsLimit) {
			pathBuffer = new float[(2+waypointsLimit)*combinedAttrsLimit];
		}
        
        if (accessor != NULL)
        {
            Block_release(accessor);
            accessor = NULL;
        }
    }
    
    void Tween::setup(Accessor accessor, float duration)
    {
        assert(duration >= 0);
        
        this->accessor = Block_copy(accessor);
		this->duration = duration;
    }
   
    // -------------------------------------------------------------------------
	// Public API
	// -------------------------------------------------------------------------

    /**
	 * Sets the easing equation of the tween. Existing equations are located in
	 * <i>aurelienribon.tweenengine.equations</i> package, but you can of course
	 * implement your owns, see {@link TweenEquation}. You can also use the
	 * {@link TweenEquations} static instances to quickly access all the
	 * equations. Default equation is Quad.INOUT.
	 * <p/>
	 *
	 * <b>Proposed equations are:</b><br/>
	 * - Linear.INOUT,<br/>
	 * - Quad.IN | OUT | INOUT,<br/>
	 * - Cubic.IN | OUT | INOUT,<br/>
	 * - Quart.IN | OUT | INOUT,<br/>
	 * - Quint.IN | OUT | INOUT,<br/>
	 * - Circ.IN | OUT | INOUT,<br/>
	 * - Sine.IN | OUT | INOUT,<br/>
	 * - Expo.IN | OUT | INOUT,<br/>
	 * - Back.IN | OUT | INOUT,<br/>
	 * - Bounce.IN | OUT | INOUT,<br/>
	 * - Elastic.IN | OUT | INOUT
	 *
	 * @return The current tween, for chaining instructions.
	 * @see TweenEquation
	 * @see TweenEquations
	 */
    Tween &Tween::ease(TweenEquation &easeEquation)
    {
		this->equation = &easeEquation;
		return *this;
    }
    
    /**
	 * Sets the target value of the interpolation. The interpolation will run
	 * from the <b>value at start time (after the delay, if any)</b> to this
	 * target value.
	 * <p/>
	 *
	 * To sum-up:<br/>
	 * - start value: value at start time, after delay<br/>
	 * - end value: param
	 *
	 * @param targetValue The target value of the interpolation.
	 * @return The current tween, for chaining instructions.
	 */
	Tween &Tween::target(float targetValue)
    {
		targetValues[0] = targetValue;
		return *this;
	}
    
	/**
	 * Sets the target values of the interpolation. The interpolation will run
	 * from the <b>values at start time (after the delay, if any)</b> to these
	 * target values.
	 * <p/>
	 *
	 * To sum-up:<br/>
	 * - start values: values at start time, after delay<br/>
	 * - end values: params
	 *
	 * @param targetValue1 The 1st target value of the interpolation.
	 * @param targetValue2 The 2nd target value of the interpolation.
	 * @return The current tween, for chaining instructions.
	 */
	Tween &Tween::target(float targetValue1, float targetValue2)
    {
		targetValues[0] = targetValue1;
		targetValues[1] = targetValue2;
		return *this;
	}
    
	/**
	 * Sets the target values of the interpolation. The interpolation will run
	 * from the <b>values at start time (after the delay, if any)</b> to these
	 * target values.
	 * <p/>
	 *
	 * To sum-up:<br/>
	 * - start values: values at start time, after delay<br/>
	 * - end values: params
	 *
	 * @param targetValue1 The 1st target value of the interpolation.
	 * @param targetValue2 The 2nd target value of the interpolation.
	 * @param targetValue3 The 3rd target value of the interpolation.
	 * @return The current tween, for chaining instructions.
	 */
	Tween &Tween::target(float targetValue1, float targetValue2, float targetValue3)
    {
		targetValues[0] = targetValue1;
		targetValues[1] = targetValue2;
		targetValues[2] = targetValue3;
		return *this;
	}

    Tween &Tween::target(float *targetValues, int len)
    {
        if (len <= combinedAttrsLimit)
        {
            for (int i=0; i<len; i++)
                this->targetValues[i] = targetValues[i];
        }
		return *this;
    }

    /**
	 * Sets the target value of the interpolation, relatively to the <b>value
	 * at start time (after the delay, if any)</b>.
	 * <p/>
	 *
	 * To sum-up:<br/>
	 * - start value: value at start time, after delay<br/>
	 * - end value: param + value at start time, after delay
	 *
	 * @param targetValue The relative target value of the interpolation.
	 * @return The current tween, for chaining instructions.
	 */
	Tween &Tween::targetRelative(float targetValue)
    {
		isRelative = true;
		targetValues[0] = isInitialized() ? targetValue + startValues[0] : targetValue;
		return *this;
	}
    
	/**
	 * Sets the target values of the interpolation, relatively to the <b>values
	 * at start time (after the delay, if any)</b>.
	 * <p/>
	 *
	 * To sum-up:<br/>
	 * - start values: values at start time, after delay<br/>
	 * - end values: params + values at start time, after delay
	 *
	 * @param targetValue1 The 1st relative target value of the interpolation.
	 * @param targetValue2 The 2nd relative target value of the interpolation.
	 * @return The current tween, for chaining instructions.
	 */
	Tween &Tween::targetRelative(float targetValue1, float targetValue2)
    {
		isRelative = true;
		targetValues[0] = isInitialized() ? targetValue1 + startValues[0] : targetValue1;
		targetValues[1] = isInitialized() ? targetValue2 + startValues[1] : targetValue2;
		return *this;
	}
    
	/**
	 * Sets the target values of the interpolation, relatively to the <b>values
	 * at start time (after the delay, if any)</b>.
	 * <p/>
	 *
	 * To sum-up:<br/>
	 * - start values: values at start time, after delay<br/>
	 * - end values: params + values at start time, after delay
	 *
	 * @param targetValue1 The 1st relative target value of the interpolation.
	 * @param targetValue2 The 2nd relative target value of the interpolation.
	 * @param targetValue3 The 3rd relative target value of the interpolation.
	 * @return The current tween, for chaining instructions.
	 */
	Tween &Tween::targetRelative(float targetValue1, float targetValue2, float targetValue3)
    {
		isRelative = true;
		targetValues[0] = isInitialized() ? targetValue1 + startValues[0] : targetValue1;
		targetValues[1] = isInitialized() ? targetValue2 + startValues[1] : targetValue2;
		targetValues[2] = isInitialized() ? targetValue3 + startValues[2] : targetValue3;
		return *this;
	}
    
	/**
	 * Sets the target values of the interpolation, relatively to the <b>values
	 * at start time (after the delay, if any)</b>.
	 * <p/>
	 *
	 * To sum-up:<br/>
	 * - start values: values at start time, after delay<br/>
	 * - end values: params + values at start time, after delay
	 *
	 * @param targetValues The relative target values of the interpolation.
	 * @return The current tween, for chaining instructions.
	 */
	Tween &Tween::targetRelative(float *targetValues, int len)
    {
        if (len <= combinedAttrsLimit)
        {
            for (int i=0; i<len; i++)
                this->targetValues[i] = isInitialized() ? targetValues[i] + startValues[i] : targetValues[i];
        }
        
		isRelative = true;
		return *this;
	}

    /**
	 * Adds a waypoint to the path. The default path runs from the start values
	 * to the end values linearly. If you add waypoints, the default path will
	 * use a smooth catmull-rom spline to navigate between the waypoints, but
	 * you can change this behavior by using the {@link #path(TweenPath)}
	 * method.
	 * <p/>
	 * Note that if you want waypoints relative to the start values, use one of
	 * the .targetRelative() methods to define your target.
	 *
	 * @param targetValue1 The 1st target of this waypoint.
	 * @param targetValue2 The 2nd target of this waypoint.
	 * @return The current tween, for chaining instructions.
	 */
	Tween &Tween::waypoint(float targetValue1, float targetValue2)
    {
		if (waypointsCnt < waypointsLimit)
        {
            waypoints[waypointsCnt*2] = targetValue1;
            waypoints[waypointsCnt*2+1] = targetValue2;
            waypointsCnt += 1;
        }
        
		return *this;
	}
    
	/**
	 * Adds a waypoint to the path. The default path runs from the start values
	 * to the end values linearly. If you add waypoints, the default path will
	 * use a smooth catmull-rom spline to navigate between the waypoints, but
	 * you can change this behavior by using the {@link #path(TweenPath)}
	 * method.
	 * <p/>
	 * Note that if you want waypoints relative to the start values, use one of
	 * the .targetRelative() methods to define your target.
	 *
	 * @param targetValue1 The 1st target of this waypoint.
	 * @param targetValue2 The 2nd target of this waypoint.
	 * @param targetValue3 The 3rd target of this waypoint.
	 * @return The current tween, for chaining instructions.
	 */
	Tween &Tween::waypoint(float targetValue1, float targetValue2, float targetValue3)
    {
		if (waypointsCnt < waypointsLimit)
        {
            waypoints[waypointsCnt*3] = targetValue1;
            waypoints[waypointsCnt*3+1] = targetValue2;
            waypoints[waypointsCnt*3+2] = targetValue3;
            waypointsCnt += 1;
        }
		return *this;
	}
    
	/**
	 * Adds a waypoint to the path. The default path runs from the start values
	 * to the end values linearly. If you add waypoints, the default path will
	 * use a smooth catmull-rom spline to navigate between the waypoints, but
	 * you can change this behavior by using the {@link #path(TweenPath)}
	 * method.
	 * <p/>
	 * Note that if you want waypoints relative to the start values, use one of
	 * the .targetRelative() methods to define your target.
	 *
	 * @param targetValues The targets of this waypoint.
	 * @return The current tween, for chaining instructions.
	 */
	Tween &Tween::waypoint(float *targetValues, int len)
    {
		if (waypointsCnt < waypointsLimit)
        {
            for (int i=0; i<len; i++)
                this->waypoints[waypointsCnt*len+i] = targetValues[i];
            waypointsCnt += 1;
        }
		return *this;
	}
    
	/**
	 * Sets the algorithm that will be used to navigate through the waypoints,
	 * from the start values to the end values. Default is a catmull-rom spline,
	 * but you can find other paths in the {@link TweenPaths} class.
	 *
	 * @param path A TweenPath implementation.
	 * @return The current tween, for chaining instructions.
	 * @see TweenPath
	 * @see TweenPaths
	 */
	Tween &Tween::path(TweenPath &path)
    {
		this->pathAlgorithm = &path;
		return *this;
	}

    // -------------------------------------------------------------------------
	// Getters
	// -------------------------------------------------------------------------

	/**
	 * Gets the easing equation.
	 */
	TweenEquation *Tween::getEasing() { return equation; }
    
	/**
	 * Gets the target values. The returned buffer is as long as the maximum
	 * allowed combined values. Therefore, you're surely not interested in all
	 * its content. Use {@link #getCombinedTweenCount()} to get the number of
	 * interesting slots.
	 */
	float *Tween::getTargetValues() { return targetValues; }
    
	/**
	 * Gets the number of combined animations.
	 */
    int Tween::getCombinedAttributesCount() { return combinedAttrsCnt; }

    // -------------------------------------------------------------------------
	// Base Class
	// -------------------------------------------------------------------------

    Tween &Tween::build()
    {
        if (accessor != NULL)
        {
            combinedAttrsCnt = accessor(ACCESSOR_READ, accessorBuffer);
        }
        assert(combinedAttrsCnt <= combinedAttrsLimit);
		return *this;
	}
    
	void Tween::free() { pool.free(this); }
    
	void Tween::initializeOverride()
    {
        accessor(ACCESSOR_READ, startValues);
        
		for (int i=0; i<combinedAttrsCnt; i++) {
			targetValues[i] += isRelative ? startValues[i] : 0;
            
			for (int ii=0; ii<waypointsCnt; ii++) {
				waypoints[ii*combinedAttrsCnt+i] += isRelative ? startValues[i] : 0;
			}
            
			if (isFrom) {
				float tmp = startValues[i];
				startValues[i] = targetValues[i];
				targetValues[i] = tmp;
			}
		}
	}
    
	void Tween::updateOverride(int step, int lastStep, bool isIterationStep, float delta)
    {
		if (equation == NULL) return;
        
		// Case iteration end has been reached
        
		if (!isIterationStep && step > lastStep)
        {
            accessor(ACCESSOR_WRITE, isReverse(lastStep) ? startValues : targetValues);
			return;
		}
        
		if (!isIterationStep && step < lastStep)
        {
            accessor(ACCESSOR_WRITE, isReverse(lastStep) ? targetValues : startValues);
			return;
		}
        
		// Validation
        
		assert(isIterationStep);
		assert(getCurrentTime() >= 0);
		assert(getCurrentTime() <= duration);
        
		// Case duration equals zero
        
		if (duration < 0.00000000001f && delta > -0.00000000001f)
        {
            accessor(ACCESSOR_WRITE, isReverse(step) ? targetValues : startValues);
			return;
		}
        
		if (duration < 0.00000000001f && delta < 0.00000000001f) {
			accessor(ACCESSOR_WRITE, isReverse(step) ? startValues : targetValues);
			return;
		}
        
		// Normal behavior
        
		float time = isReverse(step) ? duration - getCurrentTime() : getCurrentTime();
		float t = equation->compute(time/duration);
        
		if (waypointsCnt == 0 || pathAlgorithm == NULL)
        {
			for (int i=0; i<combinedAttrsCnt; i++)
            {
				accessorBuffer[i] = startValues[i] + t * (targetValues[i] - startValues[i]);
			}
            
		}
        else
        {
			for (int i=0; i<combinedAttrsCnt; i++)
            {
				pathBuffer[0] = startValues[i];
				pathBuffer[1+waypointsCnt] = targetValues[i];
				for (int ii=0; ii<waypointsCnt; ii++)
                {
					pathBuffer[ii+1] = waypoints[ii*combinedAttrsCnt+i];
				}
                
				accessorBuffer[i] = pathAlgorithm->compute(t, pathBuffer, waypointsCnt+2);
			}
		}
        
		accessor(ACCESSOR_WRITE, accessorBuffer);
	}

	void Tween::forceStartValues()
    {
		accessor(ACCESSOR_WRITE, startValues);
	}
    
	void Tween::forceEndValues()
    {
		accessor(ACCESSOR_WRITE, targetValues);
	}
    
    int Tween::getTweenCount() { return 1; }

    int Tween::getTimelineCount() { return 0; }

}