#include "Game.h"


#define WIDTH 1920
#define HEIGHT 1080
#define OFFSET_X 64
#define OFFSET_Y 64

#define RADIAN(a) (a * (PI/180))


float boundX = WIDTH;
float boundY = HEIGHT;

// int Grid_Pos(float f){
//     int t = (int)f / TILE_SIZE;
//     return t;
// }

/*############ GamePlay Stuff #########*/
static inline void HUD(Game* game);
void  GameUpdate(Game* game);
void  NextLevel(Game* game);
void  SelectingTower(Game* game);
/*#####################################*/


/*############ UI STUFF ##############*/
void ShowCards(Game* game);
void ShowHud(Game* game);
void UiSelectingTower(Game* game);
/*####################################*/


Game* InitGame(){
    Game* game = calloc(1, sizeof(Game));
    game->entt = InitEntities();
    // Init_TowerSystem(&game->towers);
    Init_Map(&game->map);
    // Init_ProjectileSystem(&game->projects);

    game->ui = UIManager_Create(20);

    game->camera = (Camera2D){0};
    game->camera.target = (Vector2){(MAP_WIDTH * TILE_SIZE * 0.5f),(MAP_HEIGHT * TILE_SIZE * 0.5f)};
    game->camera.rotation = 0;
    game->camera.offset = (Vector2){GetScreenWidth()  * 0.5f,GetScreenHeight() * 0.5f};
    game->camera.zoom = 1.0f;
    game->current_state = GAME_RUNNING;
    game->ui_state = UI_STATE_MAIN_GAME;

    game->cards.cards_selected = NULL;

    return game;
}
void DestroyGame(Game *game)
{
    if (!game) return;

    if (game->ui) {
        UIManager_Destroy(game->ui);
        game->ui = NULL;
    }
    MemFree(game);
}





void Run(){
    
    SetRandomSeed(time(NULL));
    
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(WIDTH,HEIGHT,"Rogue Not Like");
    SetTargetFPS(60);

    Game* game = InitGame();
    // game->camera.target = (Vector2){
    //     (game->grid->collums  * TILE_SIZE * 0.5f),
    //     (game->grid->rows * TILE_SIZE * 0.5f)
    // };

    float zoom = 2.0;
    game->current_state = GAME_RUNNING;


    for (size_t i = 0; i < 5; i++)
    {
        int card_id = GetRandomValue(0,CARD_ID_COUNT -1);
        game->cards.deck[i] = new_card_by_id(card_id);
        game->cards.deck_count++;
    }


    while (!WindowShouldClose())
    {
        InputUpdate(&game->input,game->camera);
        Ui_Reset(game->ui);
        game->ui->scale = uiScale();
        float baseWidth = 1280.0f;

        switch (game->current_state)
        {
        case MAIN_MENU:
        
            break;
        case GAME_RUNNING:
                GameUpdate(game);
            break;
        case CHANGING_LEVEL:
            break;
        case SELECTING_CARD:
            break;
        default:
            break;
        }        
    }
    DestroyGame(game);
    CloseWindow();
}


void GameUpdate(Game* game){
    UpdateCam(game);
    BeginDrawing();
    ClearBackground(BLUE);
    /*############ RENDER DA UI  ###########*/

    switch (game->ui_state)
    {
        case UI_STATE_MAIN_GAME:
        UpdateEntities(&game->entt,&game->input,&game->map);
        Map_Update(&game->map,&game->input);
        break;
        //UpdateGrid(game);
        //UpdateTowers(game);
        // if(UI_Button(game,(Rectangle){20,100,40,40},"Select Tower")){
        //     game->ui_state = UI_STATE_SELECTING_TOWER;
        // }
        //Map_Update(&game->map,&game->input);
    default:
        break;
    }
    
    /*############ RENDER DE OBJETOS DENTRO DO GAME ###########*/
    BeginMode2D(game->camera);
    Map_Draw(&game->map);
    tower_draw(&game->entt.t_system);
    EndMode2D();

    DrawFPS(10,10);
    UI_Render(game);
    EndDrawing();
    return;

}

void UpdateCam(Game* game)
{
    float scaleX = (float)GetScreenWidth()  / WIDTH;
    float scaleY = (float)GetScreenHeight() / HEIGHT;

    // Mantém proporção
    float scale = (scaleX < scaleY) ? scaleX : scaleY;

    game->camera.zoom = scale * 1.5;

    game->camera.offset = (Vector2){
        GetScreenWidth()  * 0.5f,
        GetScreenHeight() * 0.5f
    };

    // Centro do mapa
    // game->camera.target = (Vector2){
    //     (game->grid->collums * TILE_SIZE) * 0.5f + OFFSET_X,
    //     (game->grid->rows    * TILE_SIZE) * 0.5f + OFFSET_Y
    // };
    return;
}

// void UpgradeTower(Game* game,Card* card){
//     for (int i = 0; i < game->towers.tower_count; i++)
//     {
//         Tower* t = &game->towers.towers[i];
//         t->hovered = false;
//         if(CheckCollisionPointRec(game->input.mouse_world_pos,(Rectangle){TILE_SIZE,TILE_SIZE,t->pos.x,t->pos.y})){
//             t->hovered = true;
//             if(game->input.mouse_pressed && !game->input.consumed){
//                 modify_tower_stats(t,card);
//             }
//         }
//     }
// }
