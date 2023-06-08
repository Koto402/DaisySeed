#include "Page.h"


Page::Page(AbstractEffect* fx)
{
    _fx = fx;
    _nSubPage = 0;
}

AbstractEffect* Page::GetEffect()
{
    return _fx;
}

void Page::UpdateSubPage(int increment)
{
    _nSubPage = increment;
}