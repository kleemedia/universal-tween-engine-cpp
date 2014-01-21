//
//  TweenManager.cpp
//
//  This code is derived from Universal Tween Engine
//  Licensed under Apache License 2.0 - http://www.apache.org/licenses/LICENSE-2.0
//

#include "TweenManager.h"
#include "BaseTween.h"

namespace TweenEngine
{
    // -------------------------------------------------------------------------
    // Static API
    // -------------------------------------------------------------------------
    
    /**
     * Disables or enables the "auto remove" mode of any tween manager for a
     * particular tween or timeline. This mode is activated by default. The
     * interest of desactivating it is to prevent some tweens or timelines from
     * being automatically removed from a manager once they are finished.
     * Therefore, if you update a manager backwards, the tweens or timelines
     * will be played again, even if they were finished.
     */
    void TweenManager::setAutoRemove(BaseTween &object, bool value)
    {
        object.isAutoRemoveEnabled = value;
    }
    
    /**
     * Disables or enables the "auto start" mode of any tween manager for a
     * particular tween or timeline. This mode is activated by default. If it
     * is not enabled, add a tween or timeline to any manager won't start it
     * automatically, and you'll need to call .start() manually on your object.
     */
    void TweenManager::setAutoStart(BaseTween &object, bool value)
    {
        object.isAutoStartEnabled = value;
    }
    
    int getTweensCount(std::vector<BaseTween *> objs)
    {
		int cnt = 0;
		for (int i=0, n=objs.size(); i<n; i++)
        {
            cnt += objs[i]->getTweenCount();
		}
		return cnt;
	}
    
	int getTimelinesCount(std::vector<BaseTween *> objs)
    {
		int cnt = 0;
		for (int i=0, n=objs.size(); i<n; i++)
        {
            cnt += objs[i]->getTimelineCount();
		}
		return cnt;
	}
    
    bool isTweenFinished(BaseTween *obj)
    {
        if (obj->isFinished() && obj->isAutoRemoveEnabled)
        {
            obj->free();
            return true;
        }
        return false;
    }

    // -------------------------------------------------------------------------
	// API
	// -------------------------------------------------------------------------

    TweenManager::TweenManager() : objects()
    {
        objects.reserve(20);
    }

    /**
	 * Adds a tween or timeline to the manager and starts or restarts it.
	 *
	 * @return The manager, for instruction chaining.
	 */
	TweenManager &TweenManager::add(BaseTween &object)
    {
        bool isPresent = (std::find(objects.begin(), objects.end(), &object) != objects.end());
		if (!isPresent) objects.push_back(&object);
		if (object.isAutoStartEnabled) object.start();
		return *this;
	}
    
	/**
	 * Kills every managed tweens and timelines.
	 */
	void TweenManager::killAll()
    {
		for (int i=0, n=objects.size(); i<n; i++)
        {
			BaseTween *obj = objects[i];
			obj->kill();
		}
	}
    
	/**
	 * Increases the minimum capacity of the manager. Defaults to 20.
	 */
	void TweenManager::ensureCapacity(int minCapacity) { objects.reserve(minCapacity); }
    
	/**
	 * Pauses the manager. Further update calls won't have any effect.
	 */
	void TweenManager::pause() { isPaused = true; }
    
	/**
	 * Resumes the manager, if paused.
	 */
	void TweenManager::resume() { isPaused = false; }
    
	/**
	 * Updates every tweens with a delta time ang handles the tween life-cycles
	 * automatically. If a tween is finished, it will be removed from the
	 * manager. The delta time represents the elapsed time between now and the
	 * last update call. Each tween or timeline manages its local time, and adds
	 * this delta to its local time to update itself.
	 * <p/>
	 *
	 * Slow motion, fast motion and backward play can be easily achieved by
	 * tweaking this delta time. Multiply it by -1 to play the animation
	 * backward, or by 0.5 to play it twice slower than its normal speed.
	 */
   
	void TweenManager::update(float delta)
    {
        // Remove tweens that are finished
        objects.erase(std::remove_if(objects.begin(),objects.end(),isTweenFinished), objects.end());
        
		if (!isPaused)
        {
			if (delta >= 0)
            {
				for (int i=0, n=objects.size(); i<n; i++) objects[i]->update(delta);
			}
            else
            {
				for (int i=objects.size()-1; i>=0; i--) objects[i]->update(delta);
			}
		}
	}
    
	/**
	 * Gets the number of managed objects. An object may be a tween or a
	 * timeline. Note that a timeline only counts for 1 object, since it
	 * manages its children itself.
	 * <p/>
	 * To get the count of running tweens, see {@link #getRunningTweensCount()}.
	 */
	int TweenManager::size() { return objects.size(); }
    
	/**
	 * Gets the number of running tweens. This number includes the tweens
	 * located inside timelines (and nested timelines).
	 * <p/>
	 * <b>Provided for debug purpose only.</b>
	 */
	int TweenManager::getRunningTweensCount() { return getTweensCount(objects); }
    
	/**
	 * Gets the number of running timelines. This number includes the timelines
	 * nested inside other timelines.
	 * <p/>
	 * <b>Provided for debug purpose only.</b>
	 */
	int TweenManager::getRunningTimelinesCount() { return getTimelinesCount(objects); }
    
	/**
	 * Gets a list of every managed object.
	 * <p/>
	 * <b>Provided for debug purpose only.</b>
	 */
    std::vector<BaseTween *> &TweenManager::getObjects()
    {
		return objects;
	}

}
