#include "AbstractEffect.h"

class Delay : public AbstractEffect 
{
    public:
        void ProcessStereo(float fInL, float fInR, float& frOutL, float& frOutR);
        void ProcessMono(float fIn, float& fpOut);
        void SetParameterValues(int nVal1, int nVal2);
};