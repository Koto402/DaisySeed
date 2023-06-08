
#include "src/util/color.h"
#include "../../Util/Util.h"
#include "UiCurator.h"


Color::PresetColor PresetColors[] = 
{
	Color::PresetColor::RED,
	Color::PresetColor::BLUE,
	Color::PresetColor::GREEN,
};

Color* ColorObjects[ARRAY_DIM(PresetColors)];

UiCurator::UiCurator()
{
    _mainPageLed = &_hw.led1;
    _subPageLed = &_hw.led2;
    InitPageColors();
    nCurrentPage = 0;

}

void UiCurator::InitHw(AudioHandle::AudioCallback cb)
{
    _hw.Init();
	_hw.SetAudioBlockSize(4); // number of samples handled per callback
	_hw.SetAudioSampleRate(SaiHandle::Config::SampleRate::SAI_48KHZ);
	_hw.StartAdc();
	_hw.StartAudio(cb);
}

UiCurator* UiCurator::_uiCurator = nullptr;

UiCurator* UiCurator::GetInstance()
{
    if(_uiCurator == nullptr)
    {
        _uiCurator = new UiCurator();
    }
    return (_uiCurator);
}

void UiCurator::InitPageColors()
{
	for (size_t i = 0; i < ARRAY_DIM(ColorObjects); i++)
	{
		ColorObjects[i] = new Color();
		ColorObjects[i]->Init(PresetColors[i]);
	}
}

void UiCurator::ProcessIo()
{
    _hw.ProcessAllControls();

    UpdatePage();
    float knob_val_1 = _hw.GetKnobValue(_hw.KNOB_1);	
 	float knob_val_2 = _hw.GetKnobValue(_hw.KNOB_2);
    
    //AbstractEffect* fxPtr = _fxList[nCurrentFx];
    //fxPtr->SetParameterValues(nSubPage, knob_val_1, knob_val_2);

    //_pageList[nCurrentPage]._fx->SetParameterValues(nSubPage,)
    return;
}

void UiCurator::ProcessAudio(float fIn, float &fOut)
{
    AbstractEffect* pFx = _pageList[nCurrentPage].GetEffect();
    pFx->ProcessMono(fIn,fOut);
}

void UiCurator::UpdatePage()
{
    int increment = _hw.encoder.Increment();
    if(increment == 0)
        return;

    nCurrentPage += increment;
    int max_size = _pageList.size();
    nCurrentPage = (nCurrentPage >= max_size) ? max_size - 1 : nCurrentPage;
    nCurrentPage = (nCurrentPage < 0) ? 0 : nCurrentPage;
    _mainPageLed->SetColor(*ColorObjects[nCurrentPage]);
    _mainPageLed->Update();
}

void UiCurator::UpdateSubPage()
{ 
    //If only one button was pressed 
    if(_hw.button1.RisingEdge() ^ _hw.button2.RisingEdge())
    {
        int IncrementVal = 0;
        IncrementVal = _hw.button1.RisingEdge() ? (-1) : (1);
        _pageList[nCurrentPage].UpdateSubPage(IncrementVal);
    }
}

void UiCurator::AddFx(AbstractEffect* fxPtr)
{
    _pageList.push_back(fxPtr);
}

void UiCurator::UpdateLeds()
{
    return;
}
