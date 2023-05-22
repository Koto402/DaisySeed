#include "Color.h"

const float aStandardColors[enPresetColor_Count][3] = {
    {0.0f, 0.0f, 0.0f},   // OFF
    {1.0f, 0.0f, 0.0f},   // RED
    {0.0f, 1.0f, 0.0f},   // GREEN
    {0.0f, 0.0f, 1.0f},   // BLUE
    {1.0f, 1.0f, 1.0f},   // WHITE
    {0.25f, 0.0f, 1.0f},  // PURPLE
    {0.0f, 0.25f, 0.75f}, // CYAN
    {1.0f, 0.33f, 0.0f},  // GOLD
};

void Color::Init(PresetColor_t c)
{
    _red   = aStandardColors[c][0];
    _green = aStandardColors[c][1];
    _blue  = aStandardColors[c][2];
}