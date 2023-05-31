
#ifndef UI_CURATOR_H
#define UI_CURATOR_H

#include "..\Page\Page.h"
#include "..\..\Util\util.h"
#include "daisy_pod.h"

class UiCurator
{
    public:
    static UiCurator* GetInstance();

    protected:    
    UiCurator();
    static UiCurator* _uiCurator;
    
    private:

    void InitPageColors();
    Color::PresetColor _presetColors[] = 
    {
        Color::PresetColor::RED,
        Color::PresetColor::BLUE,
        Color::PresetColor::GREEN,
    };
    Color* _colorObjects[ARRAY_DIM(_presetColors)];
};



#endif /* UI_CURATOR_H */
