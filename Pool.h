//
//  Pool.h
//
//  This code is derived from Universal Tween Engine
//  Licensed under Apache License 2.0 - http://www.apache.org/licenses/LICENSE-2.0
//

/**
 * A light pool of objects that can be resused to avoid allocation.
 * Based on Nathan Sweet pool implementation
 */

#ifndef __Pool__
#define __Pool__

#include <vector>

namespace TweenEngine
{
    
    template<typename T>
    class PoolCallback
    {
    public:
        virtual void onPool(T *obj) = 0;
        virtual void onUnPool(T *obj) = 0;
    };
    
    template<typename T>
    class Pool
    {
    private:
        std::vector<T *> objects;
        PoolCallback<T> *callback;
        
    protected:
        virtual ~Pool() {}
        virtual T *create()=0;
        
    public:
        Pool(int initCapacity, PoolCallback<T> *callback);
        T *get();
        void free(T *obj);
        void clear();
        int size();
        void ensureCapacity(int minCapacity);
        
    };
    
    // Implementation
    template <typename T>
    Pool<T>::Pool(int initCapacity, PoolCallback<T> *cb) : objects(initCapacity), callback(cb)
    {
    }
    
    template <typename T>
    T *Pool<T>::get()
    {
		T *obj = NULL;
        if (objects.empty())
        {
            obj = create();
        }
        else
        {
            obj = objects.back();
            objects.pop_back();
            if (obj == NULL) obj = create();
        }
		if (callback != NULL) callback->onUnPool(obj);
		return obj;
	}
    
    template <typename T>
	void  Pool<T>::free(T *obj)
    {
		if (obj == NULL) return;
        
        bool contains = (std::find(objects.begin(), objects.end(), obj) != objects.end());
        
		if (!contains)
        {
			if (callback != NULL) callback->onPool(obj);
			objects.push_back(obj);
		}
	}
    
    template <typename T>
	void  Pool<T>::clear() { objects.clear(); }
    
    template <typename T>
	int  Pool<T>::size() { return objects.size(); }
    
    template <typename T>
    void  Pool<T>::ensureCapacity(int minCapacity) { objects.reserve(minCapacity); }

}

#endif /* defined(__Pool__) */
