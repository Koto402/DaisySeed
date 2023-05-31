#include "UiCurator.h"


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