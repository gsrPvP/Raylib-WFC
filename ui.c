#include "ui.h"
#include "Game.h"

float uiScale(){
    float scaleX = (float)GetScreenWidth() / 1280.0f;
    float scaleY = (float)GetScreenHeight() / 720.0f;

    float scale = fminf(scaleX,scaleY);
    return scale;
}


UIManager* UIManager_Create(int capacity){
    UIManager *ui = malloc(sizeof(UIManager));
    ui->elements = malloc(sizeof(UIElement) * capacity);
    ui->capacity = capacity;
    ui->count = 0;
    ui->nextId = 1;
    ui->font = GetFontDefault();
    ui->fontSize =20;
    ui->scale = uiScale();

    return ui;
}

void UIManager_Destroy(UIManager *ui){
    MemFree(ui->elements);
    MemFree(ui);
} 

void Ui_Reset(UIManager* ui){
    ui->count = 0;
    ui->nextId =1;
}

static UIElement *UIManager_AddElement(UIManager *ui, UIElementType type){

    if(ui->count >= ui->capacity) return NULL;

    UIElement *elem = &ui->elements[ui->count++];
    memset(elem,0,sizeof(UIElement));

    elem->id = ui->nextId++;
    elem->type = type;
    elem->bgColor = LIGHTGRAY;
    elem->textColor = BLACK;
    
    return elem;
}

bool UI_ButtonRect(Game *game, Rectangle rect, const char *text) {
    UIElement *elem = UIManager_AddElement(game->ui, UI_BUTTON_RECT);
    if (!elem) return 0;
    elem->bounds.rect = rect;
    Vector2 virtualMouse = {
    game->input.mouse_pos.x / uiScale(),
    game->input.mouse_pos.y / uiScale()
};
    strncpy(elem->text,text,sizeof(elem->text)-1);
    elem->text[sizeof(elem->text) -1 ] = '\0';
    elem->hovered = CheckCollisionPointRec(virtualMouse,elem->bounds.rect);
    if(elem->hovered && game->input.mouse_pressed && !game->input.consumed){
        game->input.consumed = true;
        return true;
    }

    return false;
}

int UI_PanelRect(UIManager *ui,Rectangle rect,Color color){
    UIElement *elem = UIManager_AddElement(ui,UI_PANEL);
    if (!elem) return 0;

    elem->bgColor = color;
    elem->bounds.rect = rect;
    return elem->id;
}


int UI_Label(UIManager *ui, Vector2 pos,const char *text) {
    UIElement *elem = UIManager_AddElement(ui, UI_LABEL);
    if (!elem) return 0;
    
    elem->pos = pos;
    strncpy(elem->text,text,sizeof(elem->text)-1);
    elem->text[sizeof(elem->text)-1] = '\0';
    elem->bgColor = WHITE; // Transparente
    
    return elem->id;
}

int btn_Tower(Game* game,int id_tower,Vector2 pos , float radius,const char* text){
        UIElement *elem = UIManager_AddElement(game->ui, UI_BUTTON_CIRCLE);
    if (!elem) return 0;
    
    elem->bounds.circle = (Circle){pos,radius};
    elem->value = id_tower;
    strncpy(elem->text,text,sizeof(elem->text)-1);
    elem->text[sizeof(elem->text) -1 ] = '\0';
    elem->bgColor = GRAY;
    if(elem)
    elem->hovered = CheckCollisionPointCircle(game->input.mouse_pos,elem->bounds.circle.center,elem->bounds.circle.radius);
    if(elem->hovered && game->input.mouse_pressed && !game->input.consumed){
        game->input.consumed = true;
        return elem->value;
    }

    return -1;
}

void UI_Render(Game *game) {
    for (int i = 0; i < game->ui->count; i++) {
        UIElement *elem = &game->ui->elements[i];
        
        switch (elem->type) {
            case UI_BUTTON_RECT: {

                Color bg = elem->bgColor;
                if (elem->pressed) bg = WHITE;
                else if (elem->hovered) bg = DARKGRAY;
                
                Rectangle scaled_rect = (Rectangle){
                    elem->bounds.rect.x * game->ui->scale,
                    elem->bounds.rect.y * game->ui->scale,
                    elem->bounds.rect.width * game->ui->scale,
                    elem->bounds.rect.height * game->ui->scale,
                };

                DrawRectangleRounded(scaled_rect, 0.2f,10,bg);
                DrawRectangleRoundedLinesEx(scaled_rect,0.2,10, 2, BLACK);
                
                Vector2 textSize = MeasureTextEx(game->ui->font, elem->text, game->ui->fontSize, 1);
                Vector2 textPos = {
                    scaled_rect.x + (scaled_rect.width- textSize.x) / 2,
                    scaled_rect.y + (scaled_rect.height - game->ui->fontSize * game->ui->scale) / 1.25
                };
                DrawTextEx(game->ui->font, elem->text, textPos, game->ui->fontSize * game->ui->scale, 1, elem->textColor);
                break;
            }
            
            case UI_LABEL: {
                    // Rectangle scaled_rect = (Rectangle){
                    //     elem->bounds.rect.x * game->ui->scale,
                    //     elem->bounds.rect.y * game->ui->scale,
                    //     elem->bounds.rect.width * game->ui->scale,
                    //     elem->bounds.rect.height * game->ui->scale,
                    // };
                // if (elem->bgColor.a > 0) {
                //     DrawRectangleRounded(scaled_rect,0.2f,10, elem->bgColor);
                // }
                DrawTextEx(game->ui->font, elem->text, 
                          (Vector2){elem->pos.x, elem->pos.y}, 
                          game->ui->fontSize * game->ui->scale, 1, elem->textColor);
                break;
            }
            case UI_PANEL:
                if (elem->bgColor.a > 0) {
                    Rectangle scaled_rect = (Rectangle){
                        elem->bounds.rect.x * game->ui->scale,
                        elem->bounds.rect.y * game->ui->scale,
                        elem->bounds.rect.width * game->ui->scale,
                        elem->bounds.rect.height * game->ui->scale,
                    };
                    DrawRectangleRounded(scaled_rect,0.2,10,elem->bgColor);
                }break;

            case UI_BUTTON_CIRCLE:
                    Color bg = elem->bgColor;
                    if (elem->pressed) bg = WHITE;
                    else if (elem->hovered) bg = DARKGRAY;

                    Circle c = elem->bounds.circle;
                    
                    //c.radius = game->camera.zoom;
                    DrawCircle(c.center.x,c.center.y,c.radius,bg);
                    //DrawTextEx(game->ui->font, elem->text, c.center, game->ui->fontSize, 1, elem->textColor);
                break;
        }
    }
    // Reset para próximo frame
}