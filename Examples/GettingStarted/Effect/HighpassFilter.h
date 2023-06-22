#pragma once

#include "AbstractEffect.h"
#include "stdlib.h"
#include "stdint.h"
#include "../Util/util.h"
#include <math.h>
#include "../DaisySP/Source/Utility/dsp.h"

using namespace daisysp;

class HighpassFilter : public AbstractEffect
{
public:
    HighpassFilter(float cutoffFrequency, float Q, float samplerate)
    {
        Reset();
        _samplerate = samplerate;
        _cutoffFrequency = cutoffFrequency;
        _Q = Q;
        InitCoefficients(_cutoffFrequency,_Q);
    }

    void InitCoefficients(float cutoffFrequency, float Q)
    {
        float theta_c = TWOPI_F *cutoffFrequency/_samplerate;
        float d = 1.0/Q;

        float beta_numerator   = 1 - ((d/2.0)*sin(theta_c));
        float beta_denominator = 1 + ((d/2.0)*sin(theta_c));

        float beta = 0.5 * (beta_numerator/beta_denominator);
        float gamma = (0.5 + beta) * (cos(theta_c));
        
        //set coefficientss
        a0 = (0.5 + beta + gamma)/2.0;
        a1 = -1 * (0.5 + beta + gamma);
        a2 = a0;

        b1 = (-2)*gamma;
        b2 = 2*beta;

        _Q = Q;
        _cutoffFrequency = cutoffFrequency;
    }

    void SetCutoffFreq(float cutoffFrequency)
    {
        InitCoefficients(cutoffFrequency, _Q);
        _cutoffFrequency = cutoffFrequency;
    }    

    void SetQ(float q)
    {
        InitCoefficients(_cutoffFrequency, q);
        _Q = q;
    }    

    void Reset()
    {
        xz_1 = 0;
        xz_2 = 0;
        yz_1 = 0;
        yz_2 = 0;
    }

    void ProcessStereo(float fInL, float fInR, float& frOutL, float& frOutR) {};
    void SetParameterValues(int parameterSet, int nVal1, int nVal2) {}; 


    void ProcessMono(float fIn, float& frOut)
    {
        frOut = (a0 * fIn) + (a1 * xz_1) + (a2 * xz_2) - (b1 * yz_1) - (b2 *yz_2);
        
        xz_2 = xz_1;
        xz_1 = fIn;
        yz_2 = yz_1;
        yz_1 = frOut;
    }

    float a0;
    float a1;
    float a2;
    float b1;
    float b2;

protected:
    float xz_1;
    float xz_2;
    float yz_1;
    float yz_2;

private:
    float _samplerate;
    float _Q;
    float _cutoffFrequency;

};