#include "Page.h"


Page::Page(AbstractEffect* fxPtr) : _secondaryColors()
{
    _fx = fxPtr;
    _primaryColor = nullptr;
    _mainPageLed = nullptr;
    _subPageLed = nullptr;
    _nSubPage = 0;
}

AbstractEffect* Page::GetEffect()
{
    return _fx;
}

void Page::SetEffect(AbstractEffect* fxPtr)
{
    _fx = fxPtr;
}

void Page::SetColors(Color* primaryColor, std::vector<Color*>* secondaryColors)
{
    _primaryColor = primaryColor;
    _secondaryColors = secondaryColors;
}

void Page::UpdateSubPage(int increment)
{
    _nSubPage = increment;
}

int Page::GetSubPage()
{
    return _nSubPage;
}

void Page::SetLedPtrs(RgbLed* mainPageLed, RgbLed* subPageLed)
{
    _mainPageLed = mainPageLed;
    _subPageLed = subPageLed;
}

void Page::UpdateLeds()
{
    _mainPageLed->SetColor(*_primaryColor);
    _subPageLed->SetColor(*(*_secondaryColors)[_nSubPage]);
    _mainPageLed->Update();
    _subPageLed->Update();
}