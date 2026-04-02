#ifndef CARDS_H
#define CARDS_H

#include "raylib.h"
#include "stats.h"

/*Forward Declarations*/
typedef struct Game Game;
typedef struct EnemySystem EnemySystem;
typedef struct Map Map;
typedef struct Tower Tower;
typedef struct TowerSystem TowerSystem;

/*####################*/

#define MAX_DECK 5

typedef enum{
    CARD_PLACE_TOWER,
    CARD_MODIFY_TOWER,
    CARD_MODIFY_ENEMIES,
    CARD_MODIFY_GAME,
    CARD_USE_SPELL,
}CardType;

typedef enum{
    CARD_NULL,
    CARD_MORE_DAMAGE,
    CARD_RAPID_SHOT,
    CARD_IGNITE_SHOTS,
    CARD_ARCHER_TOWER,
    CARD_ID_COUNT,
}CardId;

typedef enum{
    COMMON = 0,
    RARE   = 1,
    VERY_RARE =2,
    ESPECIAL = 4,
}Rarity;


typedef struct{
    int tower_id;
}CardBuild;

typedef struct{
    Stats stats;
}CardUpgrade;

typedef struct cards
{
    int effect;
}CardUsable;



typedef struct{
    const char* name;
    const char* description;
    int type;
    int rarity;
    CardId id;
    bool selected;
    
    union
    {
        CardBuild build;
        CardUpgrade upgrade;
        CardUsable usable;
    };
    Texture2D texture;


    bool consumed;
    bool unlocked;
}Card;


typedef struct CardSystem{
    Card    *cards_selected;
    Card    *deck[5]; // array de ponteiros para cartas
    int     deck_count;
}CardSystem;

void add_stats(Stats* dst, const Stats* src);
void place_tower(Map* map,TowerSystem* ts, Vector2 world_pos, int tower_id);
void modify_tower_stats(Tower* target,Card* card);
void use_card_on_map(Map* map, Card* card, Vector2 world_pos);

void update_draw_card(Game* game,int id_card,Vector2 screen_pos);
void consume_card(CardSystem* cs, Card* card);

Card *new_card_by_id(int id);
extern Card data_cards[CARD_ID_COUNT];

#endif