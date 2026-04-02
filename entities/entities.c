#include "entities.h"


Vector2 MoveTowards(Vector2 pos, Vector2 target, float speed, float dt)
{
    Vector2 dir = Vector2Subtract(target, pos);  // direção bruta
    Vector2Normalize(dir);
    return dir;
}

EntitySystem  InitEntities(){
    EntitySystem entities;
    init_tower_system(&entities.t_system);
    init_enemy_system(&entities.e_system);
    Init_ProjectileSystem(&entities.p_system);
    // init_effect_system(&entt->ef_system);
    return entities;
}
    

void UpdateEntities(EntitySystem* entt,InputSystem* in,Map* map){

    UpdateTowers(entt,in);
    UpdateEnemies(entt,in,map);
    UpdateProjs(entt);
    UpdateEffects(entt);
}


void tower_detect(EntitySystem* entt, Tower* tower){
    tower->target_count = 0;
    for(int i = 0; i < entt->e_system.count; i++)
    {
        Enemy* enemy = &entt->e_system.enemies[i];

        if(!enemy->active)
            continue;

        float dist = Vector2Distance(tower->center, enemy->pos);

        if(dist <= tower->data.stats.value[STAT_RANGE])
        {
            tower->targets[tower->target_count++] = enemy;

            // limite máximo da torre
            if(tower->target_count >= tower->data.stats.value[STAT_MAX_TARGETS])
                break;
        }
    }
}

void UpdateTowers(EntitySystem* entt,InputSystem* input){
    for (int i = 0; i < entt->t_system.tower_count; i++)
    {
        Tower* t = &entt->t_system.towers[i];
        t->hovered = false;
        if(CheckCollisionPointRec(input->mouse_pos,(Rectangle){TILE_SIZE,TILE_SIZE,t->pos.x,t->pos.y})){
            t->hovered = true;
            if(input->mouse_pressed && !input->consumed){
                entt->t_system.selected_tower = t;
            }
        }

        tower_detect(entt,t);
        tower_shoot(entt,t);
    }
}

void tower_shoot(EntitySystem* entt, Tower* t){
    switch (t->data.type)
    {
    case TOWER_TYPE_PROJECTILE:
            for (int  i = 0; i < t->target_count; i++)
            {
                Enemy* target = t->targets[i];
                Projectile* p = instantiate_projectile(&entt->p_system,t->center);
                p->target = target;
            }
            
        break;
    case TOWER_TYPE_LASER:
            for (int  i = 0; i < t->target_count; i++)
            {
                Enemy* target = t->targets[i];
                Laser laser = {.active = true,.init_pos = t->center, .end_pos = target->pos,.thickness = 2.0f,.max_range = t->data.stats.value[STAT_RANGE]};
                if(laser_hit(laser,target->pos)){
                    damage_enemy(target,t->data.stats.value[STAT_DAMAGE]);
                }
            }
        break;
    case TOWER_TYPE_BOX_HIT:
        break;
    }
}


void UpdateEnemies(EntitySystem *ennt, InputSystem *input,Map *map){
    for (int i = 0; i < ennt->e_system.count; i++)
    {
        Enemy* enemy = &ennt->e_system.enemies[i];
        // TO DO: fazer com que o contador diminua e possa reutilizar esse slot
        if(!enemy->active)continue;
    }
    
}


void UpdateProjs(EntitySystem* entt){
    if(entt->p_system.count <= 0) return;
    for (int i = 0; i < entt->p_system.count; i++)
    {
        Projectile* p = &entt->p_system.projectiles[i];
        if(!p->active)continue;

        if(!p->target || !p->target->active){
            p->active = false;
            continue;
        }
        p->pos = MoveTowards(p->pos,p->target->pos,p->data.speed,GetFrameTime());
        Rectangle enemy_box = (Rectangle){p->target->pos.x,p->target->pos.y,p->target->size,p->target->size};
        if(bullet_hit((Capsule){p->pos,p->size},enemy_box)){
            damage_enemy(p->target,p->data.damage);
        }
    }
    
}
void UpdateEffects(EntitySystem* entt){
    for (int i = 0; i < entt->ef_system.count; i++)
    {
        Effect* effect = &entt->ef_system.effects[i];
        if(effect->timer <=0)continue;

        
        switch (effect->type)
        {
            case EFFECT_STUN:
                for (int j = 0; j < entt->e_system.count; j++)
                {
                    Enemy *enemy = &entt->e_system.enemies[j];
                    while (effect->timer > 0)
                    {
                        enemy->stuned = true;
                    }
                }
                
                break;
            //TO DO: implementar diferentes tipos de effeitos e alguns genericos
            default:
            for (int j = 0; j < entt->e_system.count; j++)
            {
                Enemy *enemy = &entt->e_system.enemies[j];
                if(CheckCollisionCircles(effect->pos,effect->range,enemy->pos,enemy->size)){
                    damage_enemy(enemy,effect->value);
                }
            }
            break;
        }
        effect->timer -= GetTime();
    }
    
}

// void Building(Game* game, Card* card){
//     int index = MAP_INDEX(game->input.mouse_world_pos.x,game->input.mouse_world_pos.y);

//     if(game->input.mouse_pressed && !game->input.consumed){
//             //t->occupied = true;
//             Instance_Tower(&game->towers,card->build.tower_id,game->input.mouse_world_pos);
//         }

//     if(index >= 0 && index < game->map.tile_count){
//         Tile *t = &game->map.grid[index];

//         if(t->data.buildable && !t->occupied){
//             t->hovered = true;
//             if(game->input.mouse_pressed && !game->input.consumed){
//                 t->occupied = true;
//                 Instance_Tower(&game->towers,card->build.tower_id,t->pos);
//             }
//         }
//     }
// }

// void Casting(Game* game, Card* card){
//     if(game->input.mouse_pressed && !game->input.consumed){
        
//     }
// }

// void UpdateGrid(Game* game)
// {
//     Map *map = &game->map;
//     InputSystem *in = &game->input;
//     if(!map) return;

//     // resetar todos
//     for(int i = 0; i < map->tile_count; i++)
//     {
//         map->grid[i].hovered = false;
//     }

//     int x = in->mouse_world_pos.x / TILE_SIZE;
//     int y = in->mouse_world_pos.y / TILE_SIZE;

//     if(x < 0 || x >= MAP_WIDTH ||
//        y < 0 || y >= MAP_HEIGHT)
//         return;

//     int i = MAP_INDEX(x,y);
//     Tile *t = &map->grid[i];

//     t->hovered = true;

//     if(in->mouse_pressed && !in->consumed)
//     {
//         t->pressed = true;
//         map->selected_tile = t;
//     }
// }