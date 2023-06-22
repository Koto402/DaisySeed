#pragma once
#ifndef UI_CURATOR_H
#define UI_CURATOR_H

#include <vector>
#include "daisy_pod.h"
#include "src/util/color.h"

#include "../Page/Page.h"
#include "../../Effect/AbstractEffect.h"


using namespace daisy;

class UiCurator
{
    public:

        UiCurator(UiCurator &other) = delete;
        void operator=(const UiCurator &) = delete;

        void ProcessIo();
        void UpdateLeds();
        void ProcessAudio(float fIn, float &fOut);
        void AddPage(Page* page);
        static UiCurator *GetInstance();
        void SetHwRef(DaisyPod* hw);

    protected:    
        UiCurator();
        static UiCurator* _uiCurator;

    private:
        void InitPageColors();
        void UpdatePage();
        void UpdateSubPage();
        Color* GetNextColor();

        std::vector<Page*> _pageList;
        std::vector<Page*>::iterator pageIt;

        DaisyPod* _hw;
        
        RgbLed* _mainPageLed;
        RgbLed* _subPageLed;

        std::vector<Color*> _colorPtrs;
};



#endif /* UI_CURATOR_H */
