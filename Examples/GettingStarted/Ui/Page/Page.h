#include "../libDaisy/src/hid/rgb_led.h"
#include "../Color/Color.h"

class Page
{
   public:
        Page(Color PageColor, int nSubPageCount);
        ~Page() {}

        //void SetKnobParameters(int nK1, int nK1);
        void UpdateSubPage(int nPageIncrement);
        void UpdateLeds();
        float Process(float fIn);
    private:
        int _subPageCount;
        int _subPage = 0;
        Color _c;

};
