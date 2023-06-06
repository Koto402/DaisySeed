#pragma once
#ifndef UI_CURATOR_H
#define UI_CURATOR_H

#include "..\Page\Page.h"
#include "daisy_pod.h"



class UiCurator
{
    public:

        //UiCurator(UiCurator &other) = delete;
        //void operator=(const UiCurator &) = delete;


        void ProcessIo();
        void UpdateLeds();
        static UiCurator *GetInstance();

    protected:    
        UiCurator();
        static UiCurator* _uiCurator;

    private:
        void InitPageColors();
        
};



#endif /* UI_CURATOR_H */
