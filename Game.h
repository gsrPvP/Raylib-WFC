#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdint.h>
#include "time.h"
#include "raylib.h"
#include <raymath.h>
#include "world.h"
#include "cards.h"
#include "input.h"
#include "ui.h"
#include "entities/entities.h"

typedef enum{
    EASY = 0,
    MEDIUM =1,
    HARD =2,
}Difficulty;


//========Forward Declarition =========
typedef struct UIManager UIManager;

void Run();

typedef enum{
    MAIN_MENU,
    GAME_RUNNING,
    OPTIONS_MENU,
    CHANGING_LEVEL,
    LOSE_GAME,
    WIN_LEVEL,
    SELECTING_CARD,
}States;

typedef enum{
    UI_STATE_MAIN_MENU,
    UI_STATE_MAIN_GAME,
    UI_STATE_SELECTING_TOWER,
    UI_STATE_UPDATING_TOWER,
    UI_STATE_SELECTING_CARD,
}UIStates;

typedef struct Game
{   
    int                         diff;
    int                         level;

    int                         current_state;
    int                         ui_state;
    
    Map                     map;
    CardSystem      cards;
    EntitySystem    entt;
    // ProjectileSystem projects;
    // TowerSystem     towers;
    // EnemySystem     enemies;
    InputSystem     input;
    UIManager         *ui;
    Camera2D           camera;
    
    int                         kills;
    int                         coins;
    float                      base_health;
}Game;




Game* InitGame();

/*Update And Draw*/
int  UpdateUI(Game* game);
void UpdateGrid(Game* game);
void UpdateCam(Game* game);



#endif