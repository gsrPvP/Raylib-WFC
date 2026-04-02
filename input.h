#pragma once

#ifndef INPUT_SYSTEM_H
#define INPUT_SYSTEM_H
#include "raylib.h"

typedef struct InputSystem InputSystem;

struct InputSystem{
    Vector2 mouse_pos;
    Vector2 mouse_screen_pos;
    Vector2 mouse_world_pos;
    bool mouse_pressed;
    bool mouse_released;
    bool mouse_down;
    bool consumed;
};

void InputUpdate(InputSystem* in,Camera2D camera);
bool InputConsumeMouse(InputSystem* in);

#endif