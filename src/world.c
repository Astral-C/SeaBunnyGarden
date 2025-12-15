#include <world.h>
#include <util.h>

static T3DModel* world_model = NULL;
static rspq_block_t* world_model_dp = NULL;
static int world_model_instance_count = 0;

void world_update(entity* self){
    self->rotation.y = fm_fmodf(get_time_s(), 6.28318530718f);
}

entity* world_new(){
    entity* world = entity_new();
    world->update = world_update;
    world->scale.x = 0.3f;
    world->scale.y = 0.3f;
    world->scale.z = 0.3f;

    if(world_model == NULL){ // alloc these if we need them and they arent currently loaded
        T3DModel* m = t3d_model_load("rom:/tidepool.t3dm");

        world_model_instance_count++;

        rspq_block_begin();
        t3d_model_draw(m);
        world_model_dp = rspq_block_end();
    }
    world->model = world_model_dp;
    return world;
}

void free_dp_deferred(void* block){
    rspq_block_free(block);
}

void world_free(entity* self){
    world_model_instance_count--;
    if(world_model_instance_count == 0){ // no more instances of this active, delete it all
        t3d_model_free(world_model);
        rdpq_call_deferred(free_dp_deferred, self->model);
        world_model = NULL;
        world_model_dp = NULL;
    }
}