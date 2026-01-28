#include <test.h>
#include <util.h>

static T3DModel* cube_model = NULL;
static rspq_block_t* cube_model_dp = NULL;
static int cube_model_instance_count = 0;

enum CubeState {
    CUBE_STATE_IDLE = 0,
    CUBE_STATE_WALK = 1,
};

void cube_think(entity* self){
    if(self->position.x > 1000 || self->position.x < -1000 || self->position.z > 1000 || self->position.z < -1000) {
        self->direction = fmodf((float)rand(), 6.28318530718f);
    }
}

void cube_update(entity* self){
    self->position.x += cos(self->direction) * self->speed;
    self->position.z += sin(self->direction) * self->speed;
}

entity* cube_new(){
    entity* cube = entity_new();
    cube->update = cube_update;
    cube->think = cube_think;
    cube->scale.x = 0.25f;
    cube->scale.y = 0.25f;
    cube->scale.z = 0.25f;
    cube->speed = 0.8f;

    if(cube_model == NULL){ // alloc these if we need them and they arent currently loaded
        cube_model = t3d_model_load("rom:/untitled.t3dm");

        cube_model_instance_count++;

        rspq_block_begin();
        t3d_model_draw(cube_model);
        cube_model_dp = rspq_block_end();
    }
    cube->model = cube_model_dp;
    return cube;
}

void cube_free(entity* self){
    cube_model_instance_count--;
    if(cube_model_instance_count == 0){ // no more instances of this active, delete it all
        t3d_model_free(cube_model);
        rdpq_call_deferred(free_dp_deferred, self->model);
        cube_model = NULL;
        cube_model_dp = NULL;
    }
}