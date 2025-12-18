#include <tidepool.h>
#include <camera.h>

#include <test.h>
#include <world.h>

entity* cube = NULL;
entity* world = NULL;

void tidepool_enter(gamestate* state){
    cube = cube_new();
    world = world_new();
}

void tidepool_update(gamestate* state){
    joypad_inputs_t joypad = joypad_get_inputs(JOYPAD_PORT_1);

    if(joypad.btn.a){
      camera_set_target(cube);
    }

    if(joypad.btn.b){
      camera_set_target(NULL);
    }

    camera_update(&joypad);
}

void tidepool_exit(gamestate* state){
    // cleanup assets
    entity_free(cube);
    entity_free(world);
}