//
//  TweenPool.cpp
//
//  This code is derived from Universal Tween Engine
//  Licensed under Apache License 2.0 - http://www.apache.org/licenses/LICENSE-2.0
//

#include "TweenPool.h"
#include "Tween.h"

namespace TweenEngine
{
    void TweenPoolCallback::onPool(Tween *obj)
    {
        obj->reset();
    }
    
    void TweenPoolCallback::onUnPool(Tween *obj)
    {
        obj->reset();
    }
    
    TweenPool::TweenPool() : Pool<TweenEngine::Tween>(20, new TweenPoolCallback())
    {
    }
    
    Tween *TweenPool::create() { return new Tween(); }

    //TweenPoolCallback *Tween::poolCallback = new TweenPoolCallback();
    //TweenPool *Tween::pool = new TweenPool(20, Tween::poolCallback);
    
    /*
     private static final Pool<Tween> pool = new Pool<Tween>(20, poolCallback) {
     @Override protected Tween create() {return new Tween();}
     };
     */
    
  
}