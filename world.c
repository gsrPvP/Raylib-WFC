#include "world.h"
#include "input.h"


TileData data_tiles[MAX_TILE_TYPES] ={
    [GRASS] = {.buildable = true, .id = GRASS},
    [PATH] = {.buildable = false, .id = PATH},
};

void Init_Map(Map *map){
    map->tile_count = MAP_WIDTH * MAP_HEIGHT;
    map->selected_tile = NULL;
    for (int i = 0; i < map->tile_count; i++)
    {
        Tile *t = &map->grid[i];
        t->hovered = false;
        t->occupied = false;
        t->pressed = false;
        t->pos = (Vector2){MAP_X(i) * TILE_SIZE,MAP_Y(i) * TILE_SIZE};
        t->data = data_tiles[GRASS];
    }
}


void Map_Update(Map* map, InputSystem *in)
{
    if(!map) return;

    // resetar todos
    for(int i = 0; i < map->tile_count; i++)
    {
        map->grid[i].hovered = false;
    }

    int x = in->mouse_world_pos.x / TILE_SIZE;
    int y = in->mouse_world_pos.y / TILE_SIZE;

    if(x < 0 || x >= MAP_WIDTH ||
       y < 0 || y >= MAP_HEIGHT)
        return;

    int i = MAP_INDEX(x,y);
    Tile *t = &map->grid[i];

    t->hovered = true;

    if(in->mouse_pressed && !in->consumed)
    {
        t->pressed = true;
        map->selected_tile = t;
    }
}



void Map_Draw(Map* map){
    if(!map)return;
        for (int y  = 0; y   < MAP_HEIGHT; y ++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            int i = y * MAP_WIDTH +x;
            Tile* t = &map->grid[i];
            Rectangle rect = (Rectangle){t->pos.x,t->pos.y,TILE_SIZE,TILE_SIZE};
            if(t->data.id == GRASS){
                if(t->hovered){
                    DrawRectangleRec(rect,WHITE);
                }else{
                    DrawRectangleRec(rect,GREEN);
                }
                DrawRectangleLinesEx(rect,1.0f,BLACK);
            }
            else if(t->data.id == PATH){
                DrawRectangleRec(rect,BROWN); // TROCAR PELAS TEXTURAS
                DrawRectangleLinesEx(rect,1.0f,BLACK);
            }
        }
        
    }
}

Vector2 get_map_coords_by_id(int id){
    
}




// Path *CreatePath(Grid *g){
//     int maxPathPoints = (g->collums * g->rows)/2;
//     Path *path = malloc(sizeof(Path));
//     path->points = malloc(sizeof(Vector2) * maxPathPoints);
//     path->count = 0;

//     Tile tile = (Tile){.color = BROWN,.data.id = PATH,.hovered = false,.occupied = false,.pressed = false};

//     /// waypoints
//     int waypoint_count  = GetRandomValue(2,7);
//     Vector2 start_point = (Vector2){GetRandomValue(4 , g->collums - 4),0};//ponto inicial , mude x - y de ordem para definir lateral ou topo
//     Vector2 end_point   = (Vector2){GetRandomValue(4 , g->collums - 4),g->rows};//ponto final

//     path->points[0] = TileCenter(start_point);
//     path->count++;

//     Vector2* waypoints  = (Vector2*)calloc(waypoint_count,sizeof(Vector2));
//     waypoints[0]        = start_point;
//     waypoints[waypoint_count -1] = end_point; // Seleciona o ultimo!

//     for(int i=1;i < waypoint_count -1;i++){     //itera sobre waypoints -1 = ignorar o ultimo
//         waypoints[i] = (Vector2){GetRandomValue(3,g->collums-3),GetRandomValue(g->rows/2 - 4, g->rows/2 + 4)};
//     }
//     //waypoint count -1 , por conta do ultimo ponto já existir!!
//     for(int p=0;p < waypoint_count-1;p++){
//         Vector2 A = waypoints[p];// não chega no ultimo ponto
//         Vector2 B = waypoints[p +1];// vai até o ultimo ponto

//         //conectar os pontos A e B
//         //int midX = A.x + (B.x - B.x)/2;//
//         int midY = A.y + (B.y -A.y) /2;//
//         while (A.y != midY) {
//             g->tiles[get_index(g,(u32)A.x,(u32)A.y)] = tile;
//             path->points[path->count++] = TileCenter((Vector2){A.x,A.y});
//             A.y += (midY > A.y) ? 1 : -1;
//         }
//         while (A.x != B.x) {
//         g->tiles[get_index(g,(u32)A.x,(u32)A.y)] = tile;
//         path->points[path->count++] = TileCenter((Vector2){A.x,A.y});
//         A.x += (B.x > A.x) ? 1 : -1;
//         }
//         while (A.y != B.y) {
//         g->tiles[get_index(g,A.x,A.y)] = tile;
//         path->points[path->count++] = TileCenter((Vector2){A.x,A.y});
//         A.y += (B.y > A.y) ? 1 : -1;
//         }
//         g->tiles[get_index(g,(u32)A.x,(u32)A.y)] = tile;
//         path->points[path->count] = TileCenter((Vector2){A.x,A.y});


//     }
//     free(waypoints);
//     return path;
// }

