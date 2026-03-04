#include <stdint.h>

#pragma pack(push,1)
struct Commands
{
    bool BUTTON_A = 0;
    bool BUTTON_B = 0;
    bool BUTTON_X = 0;
    bool BUTTON_Y = 0;
    bool BUTTON_L = 0;
    bool BUTTON_R = 0;
    bool BUTTON_WL = 0;
    bool BUTTON_WR = 0;
    uint8_t JOYSTICK_L_X = 0;
    uint8_t JOYSTICK_L_Y = 0;
    uint8_t JOYSTICK_R_X = 0;
    uint8_t JOYSTICK_R_Y = 0;
    uint8_t TRIGGER_L = 0;
    uint8_t TRIGGER_R = 0;
};
#pragma pack(pop)