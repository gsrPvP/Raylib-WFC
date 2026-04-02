#pragma once

#ifndef EFFECTS_H
#define EFFECTS_H

#include "raylib.h"

typedef enum{
    EFFECT_POISON,
    EFFECT_STUN,
    EFFECT_LIGHTNING,
    MAX_EFFECT_TYPE
}EffectType;

typedef struct{
    EffectType type;
    float value;
    float range;
    float duration;
    float timer;
    Vector2 pos;
}Effect;

typedef struct EffectSystem
{
    Effect effects[64];
    int count;

}EffectSystem;


#endif