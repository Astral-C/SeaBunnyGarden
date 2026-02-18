#include <menus.h>
#include <entity.h>
#include <world.h>
#include <seaBun.h>
#include <garden.h>

static menu garden_menu;


void garden_enter(gamestate* state) {
	menu_init(&garden_menu, 3);

	//menu_add_text(&garden_menu, "Test Text", 50, 50);
	menu_add_text(&garden_menu, "dfasfdaf", 50, 50);
	menu_item* frame = menu_add_rect_outline(&garden_menu, 12, 12, 290, 210, 4);
	frame->color = RGBA32(0xff, 0x33, 0x33, 0xff);

	//menu_add_text(&garden_menu, "Menu", 50, 50);
	//menu_add_text(&garden_menu, "Buns", 50, 20);
}

void garden_update(gamestate* state){}
void garden_exit(gamestate* state){}
void garden_draw_2d(gamestate* state){
	menu_draw(&garden_menu);
}
void garden_draw_3d(gamestate* state){}