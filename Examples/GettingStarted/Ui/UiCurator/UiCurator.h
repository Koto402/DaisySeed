#pragma once
#ifndef UI_CURATOR_H
#define UI_CURATOR_H

#include "daisy_pod.h"
#include <vector>

#include "../Page/Page.h"
#include "../../Effect/AbstractEffect.h"


using namespace daisy;

class UiCurator
{
    public:

        UiCurator(UiCurator &other) = delete;
        void operator=(const UiCurator &) = delete;

        void InitHw(AudioHandle::AudioCallback cb);
        void ProcessIo();
        void UpdateLeds();
        void ProcessAudio(float fIn, float &fOut);
        void AddFx(AbstractEffect* fxPtr);
        static UiCurator *GetInstance();

    protected:    
        UiCurator();
        static UiCurator* _uiCurator;

    private:
        void InitPageColors();
        void UpdatePage();
        void UpdateSubPage();
        std::vector<Page> _pageList;
        uint8_t nCurrentPage;
        DaisyPod _hw;
        
        RgbLed* _mainPageLed;
        RgbLed* _subPageLed;
};



#endif /* UI_CURATOR_H */
