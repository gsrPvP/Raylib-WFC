#include "cards.h"
#include "entities/entities.h"
#include "world.h"
#include "ui.h"
#include "Game.h"

void add_stats(Stats* dst, const Stats* src){
    for (int i = 0; i < MAX_STATS; i++)
    {
        dst->value[i] += src->value[i];
    }
}
void place_tower(Map* map,TowerSystem* ts ,Vector2 world_pos, int tower_id){
    int index = MAP_INDEX(world_pos.x,world_pos.y);
    map->grid[index].occupied = true;
    Vector2 tpos = map->grid[index].pos;
    instance_tower(ts,tower_id,tpos);
    // Tower new_tower = (Tower){.pos = tpos,.id = tower_id,.target_count = 0,.data = data_towers[tower_id]};
    // ts->towers[ts->tower_count++] = new_tower;
}

void modify_tower_stats(Tower* target,Card* card){
    for (int i = 0; i < MAX_STATS; i++)
    {
        target->data.stats.value[i] += card->upgrade.stats.value[i];
        TraceLog(LOG_INFO,"%s stats changed by: %.2f",target->data.name,card->upgrade.stats.value[i]);
    }
}

void use_card_on_map(Map* map, Card* card, Vector2 world_pos){
    /* To Do */
}

void update_draw_card(Game* game,int id_card,Vector2 screen_pos){
    Card *card = &data_cards[id_card];
    Rectangle rect = (Rectangle){screen_pos.x,screen_pos.y,96,96};
    if(UI_ButtonRect(game,rect,card->name)){
        game->cards.cards_selected = card;
        TraceLog(LOG_INFO,"Carta: %s   ID: %d",card->name,card->id);
    }
}


void consume_card(CardSystem* cs, Card* card){
    card->consumed = true;
    cs->deck_count--;
}

Card data_cards[CARD_ID_COUNT] = {
    [CARD_ARCHER_TOWER] = {
        .name = "Torre Arqueira",
        .description = "Posiciona um Torre Arqueira",
        .rarity = COMMON,
        .type = CARD_PLACE_TOWER,
        .build = ARCHER_TOWER,
    },
    [CARD_RAPID_SHOT] = {
        .name = "Rapid Shot",
        .description = "Aumenta o fire rate da torre",
        .rarity = COMMON,
        .type = CARD_MODIFY_TOWER,
        .upgrade.stats.value = { [STAT_FIRE_RATE] = 0.5f}
    },
    [CARD_IGNITE_SHOTS] = {
        .name = "Ignite Shots",
        .description = "Aumenta o dano de fogo da Torre",
        .rarity = COMMON,
        .type = CARD_MODIFY_TOWER,
        .upgrade.stats.value = { [STAT_FIRE_DAMAGE] = 0.1f}
    },
    [CARD_MORE_DAMAGE] = {
    .name = "Piercing Bullets",
    .description = "Aumenta o dano da Torre",
    .rarity = COMMON,
    .type = CARD_MODIFY_TOWER,
    .upgrade.stats.value = { [STAT_DAMAGE] = 1.5f}
    },
};

Card *new_card_by_id(int id){
    return &data_cards[id];
}


/*
    CARD_MORE_DAMAGE,
    CARD_RAPID_SHOT,
    CARD_IGNITE_SHOTS,
    CARD_STUN,
    CARD_ADD_TARGET,
    CARD_ARCHER_TOWER,
    CARD_ID_COUNT,
*/

