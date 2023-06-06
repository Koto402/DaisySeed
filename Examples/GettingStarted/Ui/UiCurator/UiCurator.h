#pragma once
#ifndef UI_CURATOR_H
#define UI_CURATOR_H

#include "..\Page\Page.h"
#include "daisy_pod.h"



class UiCurator
{
    public:
        static UiCurator* GetInstance();
        void ProcessIo();
        void UpdateLeds();

    protected:    
        UiCurator();
        static UiCurator* _uiCurator;
    
    private:
        void InitPageColors();
};



#endif /* UI_CURATOR_H */
