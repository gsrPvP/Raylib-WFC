#include "enemies.h"

Enemy data_enemies[ENEMY_ID_COUNT] = {
    [ENEMY_DEAD_WALKER] = {.name = "Dead Walker",.size = 12.f, .type = GROUND_ENEMY, .stats={.value = {     [STAT_HEALTH] = 25.f,    [STAT_SPEED] = 10.f,   [STAT_DAMAGE] = 1.f}}},
    [ENEMY_DEAD_VIKING] = {.name = "Dead Viking",.size = 12.f, .type = GROUND_ENEMY, .stats={.value = {         [STAT_HEALTH] = 32.f,     [STAT_SPEED] = 10.f,   [STAT_DAMAGE] = 1.f}}},
    [ENEMY_VAMPIRE_BAT] = {.name = "Vampire Bat",.size = 6.f, .type = GROUND_ENEMY, .stats={.value = {         [STAT_HEALTH] = 16.f,     [STAT_SPEED] = 15.f,   [STAT_DAMAGE] = 3.f}}},
};

void init_enemy_system(EnemySystem* e_sys){
    e_sys->count = 0;
}

void damage_enemy(Enemy* enemy, float damage){
    enemy->hp -= damage;
    if(enemy->hp <= 0){
        enemy->active = false;
    }
}
