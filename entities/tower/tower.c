#include "stats.h"
#include "tower.h"


void init_tower_system(TowerSystem* towers){
    towers->selected_tower = NULL;
    towers->tower_count = 0;
}

void instance_tower(TowerSystem* sys, int id,Vector2 pos){
    Tower t;
    t.data = data_towers[id];
    t.pos = pos;
    sys->towers[sys->tower_count] = t;
    sys->tower_count++;
}
void tower_draw(TowerSystem *sys){
    if(!sys)return;

    for (int i = 0; i < sys->tower_count; i++)
    {
        Tower* t = &sys->towers[i];
        Rectangle rect = (Rectangle){t->pos.x,t->pos.y,32,32};
        DrawRectangleRec(rect,PURPLE);
        DrawCircle(t->center.x,t->center.y,32,BLACK);
    }
    
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


DataTower data_towers[TOWER_ID_COUNT] = {
    [ARCHER_TOWER] =    {.type = TOWER_TYPE_PROJECTILE, .name = "Archer Tower",     .stats={.value={[STAT_DAMAGE] = 10,[STAT_FIRE_RATE] = 1.5f,[STAT_RANGE] = 100}}},
    [ICE_MAGE_TOWER] =  {.type = TOWER_TYPE_PROJECTILE, .name = "Ice Mage" ,        .stats={.value={[STAT_DAMAGE] = 15,[STAT_FIRE_RATE] = 2.5f,[STAT_RANGE] = 75,[STAT_SLOW] = 0.7f}}},
    [FIRE_MAGE_TOWER] = {.type = TOWER_TYPE_BOX_HIT,    .name = "Fire Mage",        .stats={.value={[STAT_DAMAGE] = 20,[STAT_FIRE_RATE] = 5.0f,[STAT_RANGE] = 50,[STAT_FIRE_DAMAGE] = 3}}},
};