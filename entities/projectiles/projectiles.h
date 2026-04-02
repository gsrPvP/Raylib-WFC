#pragma once

#ifndef PROJECTILES_H
#define PROJECTILES_H

#include "stats.h"
#include "raylib.h"

#define MAX_PROJECTILES 1024

typedef struct Enemy Enemy;
typedef struct Tower Tower;

typedef struct{
    Vector2 center;
    float radius;
}Capsule;

typedef enum{
    ARROW = 0,
    FIRE_BALL,
    ICE_SPIKE,
    CATAPULT_BALL,
}ProjectileId;

typedef struct{
    float damage;
    float speed;
}DataProjectile;

typedef struct{
    DataProjectile data;
    Enemy* target;
    bool hit;
    bool active;
    Vector2 pos;
    float size;
}Projectile;

typedef struct{
    Vector2 init_pos;
    Vector2 end_pos;
    Enemy* target;
    bool active;
    bool hit;
    float thickness;
    float max_range;
}Laser;

typedef struct ProjectileSystem{
    Projectile projectiles[MAX_PROJECTILES];
    int count;
}ProjectileSystem;

void Init_ProjectileSystem(ProjectileSystem* projects);
Projectile* instantiate_projectile(ProjectileSystem* sys,Vector2 pos);
void Projectile_Draw(ProjectileSystem* sys);

bool bullet_hit( Capsule circle, Rectangle rect);
void move_projectile(Projectile* p, Vector2 normalized_pos);

bool laser_hit(Laser laser, Vector2  target_pos);
#endif