#include "../../Util/Util.h"
#include "UiCurator.h"

static Color::PresetColor PresetColors[] = 
{
    Color::PresetColor::RED,
    Color::PresetColor::BLUE,
    Color::PresetColor::GREEN,
    Color::PresetColor::WHITE,  
    Color::PresetColor::PURPLE, 
    Color::PresetColor::CYAN,   
    Color::PresetColor::GOLD,   
};

UiCurator::UiCurator() : _pageList()
{
    _mainPageLed = &_hw->led1;
    _subPageLed = &_hw->led2;
    InitPageColors();
    pageIt = _pageList.begin();
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

void UiCurator::SetHwRef(DaisyPod* hw)
{
    _hw = hw;
}

void UiCurator::InitPageColors()
{
	for (size_t i = 0; i < ARRAY_DIM(PresetColors); i++)
	{
		_colorPtrs.push_back(new Color());
        _colorPtrs[i]->Init(PresetColors[i]);
	}
}

void UiCurator::ProcessIo()
{
    _hw->ProcessAllControls();

    UpdatePage();
    (*pageIt)->UpdateLeds();
    float knob_val_1 = _hw->GetKnobValue(_hw->KNOB_1);	
 	float knob_val_2 = _hw->GetKnobValue(_hw->KNOB_2);
    
    AbstractEffect* pFx = (*pageIt)->GetEffect();
    pFx->SetParameterValues((*pageIt)->GetSubPage(), knob_val_1, knob_val_2);
    return;
}

void UiCurator::ProcessAudio(float fIn, float &fOut)
{
    AbstractEffect* pFx = (*pageIt)->GetEffect();
    pFx->ProcessMono(fIn,fOut);
}

void UiCurator::UpdatePage()
{
    int increment = _hw->encoder.Increment();
    if(increment == 0)
        return;

    if((increment == 1) && (pageIt != _pageList.end()))
    {
        pageIt++;
    }
    else if((increment == -1) && (pageIt != _pageList.begin()))
    {
        pageIt--;
    }
    
    (*pageIt)->UpdateLeds();
}

void UiCurator::UpdateSubPage()
{ 
    //If only one button was pressed 
    if(!(_hw->button1.RisingEdge() ^ _hw->button2.RisingEdge()))
        return;
    

    int incrementVal = _hw->button1.RisingEdge() ? (-1) : 1;
    (*pageIt)->UpdateSubPage(incrementVal);
}

void UiCurator::AddPage(Page* page)
{
    _pageList.push_back(page);
    page->SetColors(GetNextColor(), &_colorPtrs);
    page->SetLedPtrs(_mainPageLed, _subPageLed);
    //if this was the first page to be added
    if(_pageList.size() == 1)
    {
        pageIt = _pageList.begin();
    }
}

void UiCurator::UpdateLeds()
{
    return;
}

Color* UiCurator::GetNextColor()
{
    static size_t current_color = 0;
    Color* colorPtr = _colorPtrs[current_color];
    current_color++;
    
    if(current_color >= _colorPtrs.size())
    {
        current_color = 0;
    }
    
    return colorPtr;
}