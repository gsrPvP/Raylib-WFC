#ifndef UI_H
#define UI_H
#include "raylib.h"
#include "stdlib.h"
#include "string.h"

#pragma once 
typedef struct Game Game;

typedef struct Circle{
    Vector2 center;
    float radius;
}Circle;

typedef enum UIElementType{
    UI_BUTTON_RECT = 0,
    UI_BUTTON_CIRCLE,
    UI_SLIDER,
    UI_LABEL,
    UI_CHECKBOX,
    UI_PANEL,
    UI_BTN_TOWER,
    UI_ELEMENT_TYPE_COUNT,
    
}UIElementType;


typedef union{
        Rectangle rect;
        Circle circle;
    }UIBounds;

typedef struct UIElement{
    int id;
    UIElementType type;
    UIBounds bounds;
    Vector2 pos;
    
    char text[64];
    bool hovered;
    bool pressed;
    bool checked;
    float value;
    Color bgColor;
    Color textColor;
    void (*onClick)(void*);
    void *callbackData;
}UIElement;


typedef struct UIManager
{
    UIElement *elements;
    int capacity;
    int count;
    int nextId;
    Font font;
    int fontSize;
    float scale;
}UIManager;

UIManager* UIManager_Create(int capacity);
void UIManager_Destroy(UIManager *ui);

//void UI_Update(UIManager *ui);
void Ui_Reset(UIManager* ui);
void UI_Render(Game *game);

int btn_Tower(Game *game,int id_tower,Vector2 pos, float radius,const char* text);

bool UI_ButtonRect(Game *game,Rectangle rect,const char *text);

int UI_PanelRect(UIManager *ui,Rectangle rect,Color color);

int UI_Label(UIManager *ui,Vector2 pos,const char *text);
//int UI_Panel(UIManager *ui,Rectangle bounds);


float uiScale();

#endif