#ifndef __garden_H__
#define __garden_H__

#include <gamestate.h>

void garden_enter(gamestate* state);
void garden_update(gamestate* state);
void garden_exit(gamestate* state);
void garden_draw_2d(gamestate* state);
void garden_draw_3d(gamestate* state);

#endif // !__garden_H__