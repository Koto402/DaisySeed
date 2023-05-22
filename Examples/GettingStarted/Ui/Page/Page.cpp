#include "Page.h"
#include "..\libDaisy\src\daisy_pod.h"
#include "..\libDaisy\src\util\color.h"

int aSubPageColor[] =
{
    Color::PresetColor::RED,
    Color::PresetColor::GREEN,
    Color::PresetColor::BLUE,
}
Page::Page(Color PageColor, int nSubPageCount) 
{
    _c = PageColor; 
    _subPageCount = nSubPageCount - 1;
    _subPageCount = (_subPageCount < 1) ? 1 : _subPageCount;
}

void Page::UpdateSubPage(int nPageIncrement)
{
    _subPage = _subPage + nPageIncrement;

    //Check if value is inside the bounds of MIN_PAGE and MAX_PAGE
    _subPage = (_subPage < 0) ? 0 : _subPage;
    _subPage = (_subPage >= _subPageCount) ? _subPageCount : _subPage; 

    Color::PresetColor sPageColor = aSubPageColors[_subPage];
    pod.led2.Set(sPageColor.r,sPageColor.g,sPageColor.b);
}

void Page::UpdateLeds()
{
    pod.led1.Set(_c.r, _c.g, _c.b);    
    pod.UpdateLeds();
}

float Page::Process(float fIn)
{
    return 0;
}