#pragma once
#ifndef ABSTRACT_EFFECT_H
#define ABSTRACT_EFFECT_H

typedef enum ParameterSet 
{
    ParameterSet_1,
    ParameterSet_2,

    ParameterSet_Count,
    ParameterSet_Last = ParameterSet_Count - 1,

    ParameterSet_DelayLength    = ParameterSet_1,
    ParameterSet_DelayFeedback  = ParameterSet_2,


} ParameterSetT;


class AbstractEffect
{
    public:        
        virtual void ProcessStereo(float fInL, float fInR, float& frOutL, float& frOutR) = 0;
        virtual void ProcessMono(float fIn, float& frOut) = 0;
        virtual void SetParameterValues(int parameterSet, int nVal1, int nVal2) = 0; 

        void SetDryLevel(float dry)
        {
            if(dry >= 0 && dry <= 1)
            {
                _dry = dry;
            }
        }

        int numParameters;

    protected: 
        float _dry = 0.5;
      
    private:

};


#endif /* ABSTRACT_EFFECT_H */