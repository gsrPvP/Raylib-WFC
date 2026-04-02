#pragma once

#include "stdio.h"
#include "raylib.h"
#include "raymath.h"

#include "stats.h"
#include "world.h"
#include "tower/tower.h"
#include "enemies/enemies.h"
#include "effects/effects.h"
#include "projectiles/projectiles.h"
#include "input.h"

typedef struct EntitySystem EntitySystem;

struct EntitySystem {
    EnemySystem e_system;
    TowerSystem t_system;
    EffectSystem ef_system;
    ProjectileSystem p_system;
};

void UpdateEffects(EntitySystem* entt);
void UpdateProjs(EntitySystem* entt );
void UpdateTowers(EntitySystem* entt,InputSystem* in);
void UpdateEnemies(EntitySystem* entt,InputSystem* in,Map* map );
void UpdateEntities(EntitySystem* entt,InputSystem* in,Map* map);

EntitySystem InitEntities();


void tower_detect(EntitySystem* entt, Tower* tower);
void tower_shoot(EntitySystem* entt, Tower* t);
Laser *instance_ray(EntitySystem* entt);

