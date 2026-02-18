#include <menus.h>
#include <entity.h>
#include <world.h>
#include <test.h>

void menu_init(menu* m, int max_items){
    m->_item_count = max_items;
    m->items = malloc_uncached(sizeof(menu_item)*max_items);
    memset(m->items, 0, sizeof(menu_item)*max_items);
}

void menu_item_set_priority(menu_item* m, int priority){

}

// init a sprite element at the next available menu item
menu_item* menu_add_image(menu* m, char* path){
    for(menu_item* item = m->items; item < m->items + m->_item_count; item++){
        if(item->in_use == 0){
            item->in_use = 1;
            item->type = IMAGE;
            item->priority = 0;
            item->selectable = 0;
            item->data.img = sprite_load(path);
            return item;
        }
    }
    
    return NULL;
}

// init a text element at the next available menu item
menu_item* menu_add_text(menu* m, const char* text, float x, float y){
    for(menu_item* item = m->items; item < m->items + m->_item_count; item++){
        if(item->in_use == 0){
            item->in_use = 1;
            item->type = TEXT;
            item->priority = 0;
            item->selectable = 0;
            item->data.text = text;
            item->x = x;
            item->y = y;
            return item;
        }
    }
    
    return NULL;
}

// init a colored rect element at the next available menu item
menu_item* menu_add_rect(menu* m, float x, float y, float w, float h){
    for(menu_item* item = m->items; item < m->items + m->_item_count; item++){
        if(item->in_use == 0){
            item->in_use = 1;
            item->type = RECT;
            item->priority = 0;
            item->selectable = 0;
            item->x = x;
            item->y = y;
            item->sx = w;
            item->sy = h;
            return item;
        }
    }
    
    return NULL;
}

menu_item* menu_add_rect_outline(menu* m, float x, float y, float w, float h, float thickness){
        for(menu_item* item = m->items; item < m->items + m->_item_count; item++){
        if(item->in_use == 0){
            item->in_use = 1;
            item->type = RECT_UNFILLED;
            item->priority = 0;
            item->selectable = 0;
            item->x = x;
            item->y = y;
            item->sx = w;
            item->sy = h;
            item->data.thickness = thickness;
            return item;
        }
    }
    
    return NULL;
}

// draws all controls of a menu
void menu_draw(menu* m){
    //todo: sort by priority once every few frames
    for(menu_item* item = m->items; item < m->items + m->_item_count; item++){
        switch(item->type){
            case RECT:
                rdpq_set_mode_fill(item->color);
                rdpq_fill_rectangle(item->x, item->y, item->x + item->sx, item->y + item->sy);
                rdpq_set_mode_standard();
                break;
            case RECT_UNFILLED:
                rdpq_set_mode_fill(item->color);
                // top
                rdpq_fill_rectangle(item->x, item->y, item->x + item->sx, item->y + item->data.thickness);
                // bottom
                rdpq_fill_rectangle(item->x, item->y + item->sy - item->data.thickness, item->x + item->sx, item->y + item->sy);
                // left
                rdpq_fill_rectangle(item->x, item->y + item->data.thickness, item->x + item->data.thickness, item->y + item->sy - item->data.thickness);
                // right
                rdpq_fill_rectangle(item->x + item->sx - item->data.thickness, item->y + item->data.thickness, item->x + item->sx, item->y + item->sy - item->data.thickness);
                rdpq_set_mode_standard();
                break;
            case IMAGE:
                if (item->data.img == NULL)break;
                rdpq_sprite_blit(item->data.img, item->x, item->y, &(rdpq_blitparms_t){
                    .scale_x = item->sx,
                    .scale_y = item->sy
                });
                break;
            case TEXT:
                rdpq_text_print(NULL, FONT_BUILTIN_DEBUG_MONO, item->x, item->y, item->data.text);
                break;
        }
    }
}

void menu_free(menu* m){
    for (menu_item* item = m->items; item < m->items + m->_item_count; item++) {
        if (item->type == IMAGE) sprite_free(item->data.img);
    }
    memset(m->items, 0, sizeof(menu_item) * m->_item_count);
    free_uncached(m->items);
    m->_item_count = 0;
}

////////
///
/// Game Menu defs go here
///
////////

static menu main_menu;
static entity* title_screen_world = NULL;

void main_menu_enter(gamestate* s){
    menu_init(&main_menu, 3);

    menu_item* frame = menu_add_rect_outline(&main_menu, 16, 16, 290, 210, 4);
    frame->color = RGBA32(0x33, 0x33, 0xff, 0xff);

    menu_add_text(&main_menu, "Test Text", 50, 50);

    menu_item* press_start = menu_add_image(&main_menu, "rom:/press_start.sprite");
    press_start->x = display_get_width() / 2 - 16;
    press_start->y = display_get_height() / 2 + 55;
    press_start->sx = 1;
    press_start->sy = 1;

    title_screen_world = world_new();

}

void main_menu_draw_2d(gamestate* s){
    menu_draw(&main_menu);

}

void main_menu_draw_3d(gamestate* s){
}

void main_menu_update(gamestate* s){
    title_screen_world->rotation.y += 0.0005f;

    joypad_inputs_t joypad = joypad_get_inputs(JOYPAD_PORT_1);

    if(joypad.btn.start){
        switch_gamestate(&GameStates.garden);
    }
    
}

void main_menu_exit(gamestate* s){
    entity_free(title_screen_world);
    menu_free(&main_menu);   
}