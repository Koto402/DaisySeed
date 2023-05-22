#include "Delay.h"


void Delay::ProcessStereo(float fInL, float fInR, float& frOutL, float& frOutR)
{
    frOutL = fInL;
    frOutR = fInR;
    return;
}
void Delay::ProcessMono(float fIn, float& frOut)
{
    frOut = fIn;
    return;
}

void Delay::SetParameterValues(int nVal1, int nVal2)
{
    return;
}