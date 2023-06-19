#pragma once
#ifndef PAGE_H
#define PAGE_H

#include <vector>
#include "daisy_pod.h"
#include "src/util/color.h"
#include "..\..\Effect\AbstractEffect.h"

using namespace daisy;

class Page
{
   public:
        Page(AbstractEffect* fxPtr);
        ~Page() {}
        AbstractEffect* GetEffect();
        void SetEffect(AbstractEffect* fxPtr);
        void SetColors(Color* primaryColor, std::vector<Color*>* secondaryColors);
        void SetLedPtrs(RgbLed* mainPageLed, RgbLed* subPageLed);
        int GetSubPage();

        void UpdateSubPage(int increment);
        void UpdateLeds();

    private:
        uint8_t _nSubPage;
        AbstractEffect* _fx;
        
        Color* _primaryColor;
        std::vector<Color*>* _secondaryColors;
        RgbLed* _mainPageLed;
        RgbLed* _subPageLed;
};

#endif /* PAGE_H */