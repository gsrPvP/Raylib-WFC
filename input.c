#include "input.h"




void InputUpdate(InputSystem* in,Camera2D camera) {
    in->mouse_pos =         GetMousePosition();
    in->mouse_world_pos =   GetScreenToWorld2D(GetMousePosition(),camera);
    in->mouse_pressed  =    IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
    in->mouse_released =    IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
    in->mouse_down     =    IsMouseButtonDown(MOUSE_LEFT_BUTTON);
    in->consumed = false;
}

bool InputSystem_ConsumeMouse(InputSystem* in) {
    if (in->mouse_pressed && !in->consumed) {
        in->consumed = true;
        return true;
    }
    return false;
}

