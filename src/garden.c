#include <menus.h>
#include <entity.h>
#include <world.h>
#include <seaBun.h>
#include <garden.h>

static menu garden_menu;

static menu_item* cursor;

static menu_item* bun1;
static menu_item* bun2;

void garden_enter(gamestate* state) {
	menu_init(&garden_menu, 6);


	cursor = menu_add_rect_outline(&garden_menu, 0, 0, 38, 38, 4);
	cursor->color = RGBA32(0xff, 0xff, 0x33, 0xff);

	bun1 = menu_add_image(&garden_menu, "rom:/bun.sprite");
	bun1->x = display_get_width() / 4;
	bun1->y = display_get_height() / 3 + 55;
	bun1->sx = 1;
	bun1->sy = 1;

	bun2 = menu_add_image(&garden_menu, "rom:/bun.sprite");
	bun2->x = display_get_width() * 3 / 4;
	bun2->y = display_get_height() / 3 + 55;
	bun2->sx = 1;
	bun2->sy = 1;

	menu_add_text(&garden_menu, "Menu", display_get_width() / 2, 50);
	menu_add_text(&garden_menu, "Bun1", bun1->x, bun1->y -30);
	menu_add_text(&garden_menu, "Bun2", bun2->x -1 , bun2->y -30);

	cursor->x = bun1->x - 2;
	cursor->y = bun1->y - 2;

}

void garden_update(gamestate* state){
	joypad_inputs_t joypad = joypad_get_inputs(JOYPAD_PORT_1);
	//if (joypad.btn.d_left) {
	if(joypad.stick_x < 0){
		if(bun1)cursor->x = bun1->x - 2;
	}
	//if (joypad.btn.d_right) {
	if (joypad.stick_x > 0){
		if(bun2)cursor->x = bun2->x -2;
	}
}
void garden_exit(gamestate* state){}
void garden_draw_2d(gamestate* state){
	menu_draw(&garden_menu);
}
void garden_draw_3d(gamestate* state){}