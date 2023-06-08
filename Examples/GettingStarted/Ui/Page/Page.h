#pragma once
#ifndef PAGE_H
#define PAGE_H

#include "daisy_pod.h"
#include "src/util/color.h"
#include "..\..\Effect\AbstractEffect.h"

using namespace daisy;

class Page
{
   public:
        Page(AbstractEffect* fx);
        ~Page() {}
        AbstractEffect* GetEffect();
        void UpdateSubPage(int increment);
    private:
        uint8_t _nSubPage;
        AbstractEffect* _fx;
        Color c;
        RgbLed* _mainPageLed;
        RgbLed* _subPageLed;
};

#endif /* PAGE_H */