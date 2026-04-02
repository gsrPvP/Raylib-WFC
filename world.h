#pragma once


#include <stdint.h>
#include <malloc.h>
#include "raylib.h"

#define TILE_SIZE 32
#define MAP_WIDTH 12
#define MAP_HEIGHT 8
#define MAP_INDEX(x,y) ((y) * MAP_WIDTH + (x))
#define MAP_X(index) ((index) % MAP_WIDTH)
#define MAP_Y(index) ((index) / MAP_WIDTH)

typedef struct EffectSystem EffectSystem;
typedef struct InputSystem InputSystem;
typedef struct TowerSystem TowerSystem;
typedef struct EnemySystem EnemySystem;
typedef struct CardSystem  CardSystem;
typedef struct Map Map;

typedef enum{
    EMPTY = 0,
    PATH =1,
    GRASS =2,
    MAX_TILE_TYPES
}TileType;

typedef struct{
    TileType id;
    bool buildable;
    Texture2D text;
}TileData;


typedef struct{
    TileData data; 
    bool occupied;
    bool hovered;
    bool pressed;
    Vector2 pos;
}Tile;

extern  TileData data_tiles[MAX_TILE_TYPES];

typedef struct {
    int count;
    Vector2 *points;
}Path;

struct Map{
    Tile grid[MAP_WIDTH * MAP_HEIGHT];
    int tile_count;
    int tile_size;
    Tile* selected_tile;
};

void Init_Map(Map* map);
void Map_Update(Map* map,InputSystem *in);
void Map_Draw(Map* map);
Vector2 get_map_coords_by_id(int id);


