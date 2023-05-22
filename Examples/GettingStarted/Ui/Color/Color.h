
typedef enum
{
    enPresetColor_Off,
    enPresetColor_Red,
    enPresetColor_Green,
    enPresetColor_Blue,

    enPresetColor_White,
    enPresetColor_Purple,
    enPresetColor_Cyan,
    enPresetColor_Gold,

    enPresetColor_Count,
    enPresetColor_Last = enPresetColor_Count - 1,
} PresetColor_t;

    {1.0f, 1.0f, 1.0f},   // WHITE
    {0.25f, 0.0f, 1.0f},  // PURPLE
    {0.0f, 0.25f, 0.75f}, // CYAN
    {1.0f, 0.33f, 0.0f},  // GOLD

class Color
{
public:
    Color() {}
    ~Color() {}
    void Init(PresetColor_t c);


private:
    float _red, _green, _blue;
};

