#pragma once

#include "raylib.h"
#include "stdio.h"

#define MAX_TOWERS 144
#define MAX_TARGETS 16


/* Forward Declarations*/
typedef struct ProjectileSystem ProjectileSystem;
typedef struct EnemySystem EnemySystem;
typedef struct EffectSystem EffectSystem;
typedef struct Enemy Enemy;


typedef enum{
    TOWER_TYPE_PROJECTILE,
    TOWER_TYPE_LASER,
    TOWER_TYPE_BOX_HIT
}TowerType;

typedef enum{
    ARCHER_TOWER = 0,
    FIRE_MAGE_TOWER,
    ICE_MAGE_TOWER,
    TOWER_ID_COUNT,
}TowerId;


typedef struct{
    TowerType type;
    const char *name;
    Stats stats;
}DataTower;


typedef struct Tower{
    TowerId     id;
    DataTower   data;
    Vector2     pos;
    Vector2     center;
    Texture2D   text;
    int         target_count;
    Enemy      *targets[MAX_TARGETS];

    bool        hovered;
    bool        clicked;
}Tower;

typedef struct TowerSystem{
    Tower   towers[MAX_TOWERS];
    int     tower_count;
    Tower  *selected_tower;
}TowerSystem;


void init_tower_system(TowerSystem* towers);
void instance_tower(TowerSystem* sys,int id, Vector2 pos);
void tower_draw(TowerSystem* sys);
//void modify_tower_stats(Tower* t, int mod , float value);

extern DataTower data_towers[TOWER_ID_COUNT];
