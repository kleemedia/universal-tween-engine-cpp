//
//  Elastic.h
//
//  This code is derived from Universal Tween Engine
//  Licensed under Apache License 2.0 - http://www.apache.org/licenses/LICENSE-2.0
//

#ifndef __Elastic__
#define __Elastic__

#include "TweenEquation.h"

namespace TweenEngine
{
    class ElasticIn : public TweenEquation
    {
    private:
        float amplitude;
        float period;
        bool isAmplitudeSet;
        bool isPeriodSet;
    public:
        ~ElasticIn();
        float compute(float t);
        const char *toString();
        void setAmplitude(float a);
        void setPeriod(float p);
    };
    
    class ElasticOut : public TweenEquation
    {
    private:
        float amplitude;
        float period;
        bool isAmplitudeSet;
        bool isPeriodSet;
    public:
        ~ElasticOut();
        float compute(float t);
        const char *toString();
        void setAmplitude(float a);
        void setPeriod(float p);
    };
    
    class ElasticInOut : public TweenEquation
    {
    private:
        float amplitude;
        float period;
        bool isAmplitudeSet;
        bool isPeriodSet;
    public:
        ~ElasticInOut();
        float compute(float t);
        const char *toString();
        void setAmplitude(float a);
        void setPeriod(float p);
    };
}

#endif /* defined(__Elastic__) */
