#pragma once
#ifndef DELAY_H
#define DELAY_H

#include "AbstractEffect.h"
#include "stdlib.h"
#include "stdint.h"
#include "../Util/util.h"



template<typename T, size_t delay_length>
class Delay : public AbstractEffect 
{
    public:
        Delay() 
        {
            memset(_delayLine, 0, delay_length*sizeof(float)); 
            Reset();
        };
        
        void Reset()
        {
            _pRead = delay_length-1;
            _fb = 0.5;
            _delay = 100;
            _frac = 0.0f;
            numParameters = 2;
        }

        void ClearDDL()
        {
            memset(_delayLine, 0, delay_length*sizeof(float)); 
        }

        void ProcessStereo(float fInL, float fInR, float& frOutL, float& frOutR)
        {
            frOutL = fInL;
            frOutR = fInR;
            return;
        }
        void ProcessMono(float fIn, float& fpOut)
        {
            //float out = (_dry * fIn) + ((1 - _dry) * )
            T a = (_fb * _delayLine[(_pRead + _delay) % delay_length]);
            T b = (_fb * _delayLine[(_pRead + _delay - 1) % delay_length]);

            fpOut = _dry * fIn +  ((1 - _dry) * (a+(b-a))); 
            _delayLine[(_pRead) % delay_length] = fpOut;
//            _delayLine[(_pRead) % delay_length]  = fIn +  (_fb * _delayLine[(_pRead + _delay) % delay_length]);
//            _delayLine[(_pRead + _delay) % delay_length] = fpOut;

            //Reset pRead if out of bounds
            _pRead = (_pRead <= 0) ? delay_length-1 : _pRead - 1;
            return;
        }

        void SetDelay(size_t delay)
        {   
            _delay = delay < delay_length ? delay : delay_length-1;
        }

        void SetParameterValues(int parameterset, int nVal1, int nVal2)
        {
            switch(parameterset)
            {
                case ParameterSet_DelayLength:
                    _delay = nVal2;
                    break;
                case ParameterSet_DelayFeedback:
                    _fb = nVal2;
                    break;
                default:
                    _delay = nVal2;
                break;
            }
            _dry = nVal1;
            return;
        }
        void SetDryLevel(float dry) 
        {
            AbstractEffect::SetDryLevel(dry);
        }

        void SetFeedback(float fb)
        {
            _fb = (fb >= 1) ? 1 : fb;
            _fb = (fb < 0)  ? 0 : fb;
        }

    private:
        T _delayLine[delay_length];
        float _fb;
        float _frac;
        size_t _pWrite;
        size_t _pRead;
        size_t _delay;
};

#endif /* DELAY_H */