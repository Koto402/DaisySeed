
#include "src/util/color.h"
#include "UiCurator.h"
#include "../../Util/Util.h"

Color::PresetColor PresetColors[] = 
{
	Color::PresetColor::RED,
	Color::PresetColor::BLUE,
	Color::PresetColor::GREEN,
};

Color* ColorObjects[ARRAY_DIM(PresetColors)];

UiCurator::UiCurator()
{
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
    return;
}
void UiCurator::UpdateLeds()
{
    return;
}