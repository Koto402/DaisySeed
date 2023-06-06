#include "UiCurator.h"
#include "src/util/color.h"
#include "../../Util/Util.h"

Color::PresetColor PresetColors[] = 
{
	Color::PresetColor::RED,
	Color::PresetColor::BLUE,
	Color::PresetColor::GREEN,
};

Color* ColorObjects[ARRAY_DIM(PresetColors)];

static void InitColors()
{
	for (int i = 0; i < ARRAY_DIM(ColorObjects); i++)
	{
		ColorObjects[i] = new Color();
		ColorObjects[i]->Init(PresetColors[i]);
	}
}

UiCurator::UiCurator()
{
}

static UiCurator::UiCurator* GetInstance()
{
    if (_uiCurator == nullptr)
    {
        _uiCurator = new UiCurator();
    }

    return &(_uiCurator);
}

UiCurator::InitPageColors()
{
	for (int i = 0; i < ARRAY_DIM(_colorObjects); i++)
	{
		_colorObjects[i] = new Color();
		_colorObjects[i]->Init(_presetColors[i]);
	}
}