#pragma once
#ifndef ABSTRACT_EFFECT_H
#define ABSTRACT_EFFECT_H


class AbstractEffect
{
    public:
        virtual void ProcessStereo(float fInL, float fInR, float& frOutL, float& frOutR) = 0;
        virtual void ProcessMono(float fIn, float& frOut) = 0;
        virtual void SetParameterValues(int nVal1, int nVal2) = 0;
};


#endif /* ABSTRACT_EFFECT_H */