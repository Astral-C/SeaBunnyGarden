#ifndef __menu_H__
#define __menu_H__

#include "defs.h"
#include <libdragon.h>
#include <t3d/t3d.h>
#include <t3d/t3dmath.h>
#include <gamestate.h>

enum menu_item_type {
    IMAGE,
    RECT,
    RECT_UNFILLED,
    TEXT
};

typedef union menu_item_data_U {
    const char* text;
    sprite_t* img;
    float thickness; // At least it's 32bit!
} menu_item_data;

typedef struct menu_item_S {
    uint8_t in_use;
    uint8_t selectable;
    uint8_t priority;
    uint8_t type;
    color_t color;
    float x, y, sx, sy;
    menu_item_data data;
} menu_item;

typedef struct menu_S {
    int _item_count;
    menu_item* items;
} menu;

void menu_init(menu* m, int max_items);
void menu_free(menu* m);
void menu_item_set_priority(menu_item* m, int priority);
menu_item* menu_add_image(menu* m, char* path);
menu_item* menu_add_text(menu* m, const char* text, float x, float y);
menu_item* menu_add_rect(menu* m, float x, float y, float w, float h);
menu_item* menu_add_rect_outline(menu* m, float x, float y, float w, float h, float thickness);

void menu_draw(menu* m);

void main_menu_enter(gamestate* s);
void main_menu_update(gamestate* s);
void main_menu_exit(gamestate* s);
void main_menu_draw_2d(gamestate* s);
void main_menu_draw_3d(gamestate* s);

#endif