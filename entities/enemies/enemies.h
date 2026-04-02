#ifndef ENEMIES_H
#define ENEMIES_H

#include "raylib.h"
#include "stats.h"

#define MAX_ENEMIES 256

typedef struct DataEnemy DataEnemy;
typedef struct Enemy Enemy;
typedef struct EnemySystem EnemySystem;

typedef enum{
    GROUND_ENEMY,
    FLYING_ENEMY,
    MINI_BOSS,
    BOSS
}EnemyType;

typedef enum{
   ENEMY_DEAD_WALKER= 0,
   ENEMY_DEAD_VIKING,
   ENEMY_VAMPIRE_BAT,
    ENEMY_ID_COUNT,
}EnemyId;

struct Enemy
{
    float size;
    EnemyType type;
    const char* name;
    Stats stats;
    Vector2 pos;
    float hp;
    bool active;
    Texture2D text; //ainda não usando

    //effects - stun,
    bool stuned;
};

struct EnemySystem{
    Enemy enemies[MAX_ENEMIES];
    int count;
};

extern Enemy data_enemies[ENEMY_ID_COUNT];

void init_enemy_system(EnemySystem* e_sys);
void Enemy_Spawn(int id);
void Enemy_Update();
void Enemy_Draw();

void damage_enemy(Enemy* enemy, float damage);

#endif