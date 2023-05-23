#include "Page.h"


Page::Page(DaisyPod *hwRef, Color* PageColor, AbstractEffect* fx)
{
    _mainPageColor = PageColor;
    _subPageColor = PageColor;
    _hwRef = hwRef;
    _mainPageLed = &(_hwRef->led1);
    _subPageLed = &(_hwRef->led2);
    _fx = fx;
}

void Page::ProcessIo()
{
    return;
}

void Page::UpdateLeds()
{
    _mainPageLed->SetColor(*_mainPageColor);
    _subPageLed->SetColor(*_subPageColor);
    _hwRef->UpdateLeds();
}

float Page::ProcessAudio(float fIn)
{
    return 0;
}