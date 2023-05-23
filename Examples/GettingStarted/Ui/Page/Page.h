#pragma once
#ifndef PAGE_H
#define PAGE_H

#include "daisy_pod.h"
#include "..\..\Effect\AbstractEffect.h"

using namespace daisy;

class Page
{
   public:
        Page(DaisyPod *hwRef, Color* PageColor, AbstractEffect* fx);
        ~Page() {}
        void ProcessIo();
        void UpdateLeds();
        float ProcessAudio(float fIn);

    private:
        AbstractEffect* _fx;
        Color* _mainPageColor;
        Color* _subPageColor;
        DaisyPod* _hwRef;
        RgbLed* _mainPageLed;
        RgbLed* _subPageLed;
        
};

#endif /* PAGE_H */