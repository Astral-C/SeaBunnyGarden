#ifndef __menu_H__
#define __menu_H__

#include "defs.h"
#include <libdragon.h>
#include <t3d/t3d.h>
#include <t3d/t3dmath.h>
#include <gamestate.h>

enum menu_item_type {
    IMAGE,
    LIST,
    TEXT
};

typedef struct menu_item_S {
    float x, y, sx, sy;
    const char* text;
    sprite_t* img;
} menu_item;

typedef struct menu_S {
    sprite_t* resources;
    int item_count;
    menu_item* items;
} menu;

void main_menu_enter(gamestate* s){}
void main_menu_update(gamestate* s){}
void main_menu_exit(gamestate* s){}

#endif