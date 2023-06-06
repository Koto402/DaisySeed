#pragma once
#ifndef ABSTRACT_EFFECT_H
#define ABSTRACT_EFFECT_H


class AbstractEffect
{
    public:        
        virtual void ProcessStereo(float fInL, float fInR, float& frOutL, float& frOutR) = 0;
        virtual void ProcessMono(float fIn, float& frOut) = 0;
        virtual void SetParameterValues(int parameterSet, int nVal1, int nVal2) = 0; 
        void SetDryLevel(float dry)
        {
            _dry = (dry >= 1) ? 1 : dry;
            _dry = (dry < 0)  ? 0 : dry;
        }

    protected: 
        float _dry = 0.5;
        int _numParameters;      
    private:

};


#endif /* ABSTRACT_EFFECT_H */