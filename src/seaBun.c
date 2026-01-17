#include <seaBun.h>
#include <util.h>

static T3DModel* seaBunEnt_model = NULL;
static rspq_block_t* seaBunEnt_model_dp = NULL;
static int seaBunEnt_model_instance_count = 0;


static seaBun* SeaBunnies = NULL;
static u32 SeaBunCount = 0;

void SeaBun_init(int count){
    SeaBunnies = (seaBun*)malloc_uncached(sizeof(seaBun)*count);
    SeaBunCount = count;
    memset(SeaBunnies, 0, sizeof(seaBun)*count);
}

void SeaBun_cleanup(){
    free_uncached(SeaBunnies);
}

void SeaBun_think(entity* self){
    //if(self->position.x > 1000 || self->position.x < -1000 || self->position.z > 1000 || self->position.z < -1000) {
    //    self->direction = fmodf((float)rand(), 6.28318530718f);
    //}
}

void SeaBun_update(entity* self){
    //self->position.x += cos(self->direction) * self->speed;
    //self->position.z += sin(self->direction) * self->speed;
}

seaBun* SeaBun_new(){
    for(int i = 0; i < SeaBunCount; i++){
        if(!SeaBunnies[i]._inUse){
            SeaBunnies[i]._inUse = 1;
            SeaBunnies[i].hat = 0;
            SeaBunnies[i].location = 0;
            SeaBunnies[i].lvl_stat = 0;
            SeaBunnies[i].strength_stat = 0;
            SeaBunnies[i].speed_stat = 0;
            SeaBunnies[i].seaBunEnt = entity_new();
            SeaBunnies[i].seaBunEnt->update = SeaBun_update;
            SeaBunnies[i].seaBunEnt->think = SeaBun_think;
            SeaBunnies[i].seaBunEnt->scale.x = 0.25f;
            SeaBunnies[i].seaBunEnt->scale.y = 0.25f;
            SeaBunnies[i].seaBunEnt->scale.z = 0.25f;
            SeaBunnies[i].seaBunEnt->speed = 0.8f;

            if(seaBunEnt_model == NULL){ // alloc these if we need them and they arent currently loaded
                seaBunEnt_model = t3d_model_load("rom:/sb.t3dm");

                seaBunEnt_model_instance_count++;

                rspq_block_begin();
                t3d_model_draw(seaBunEnt_model);
                seaBunEnt_model_dp = rspq_block_end();
            }
            SeaBunnies[i].seaBunEnt->model = seaBunEnt_model_dp;
            
            return &SeaBunnies[i];
        }
    }
    return NULL;
}

void SeaBun_free(seaBun* bun){
    if(bun == NULL) return;
    bun->_inUse = 0;
    entity_free(bun->seaBunEnt);

    seaBunEnt_model_instance_count--;
    if(seaBunEnt_model_instance_count == 0){ // no more instances of this active, delete it all
        t3d_model_free(seaBunEnt_model);
        rdpq_call_deferred(free_dp_deferred, bun->seaBunEnt->model);
        seaBunEnt_model = NULL;
        seaBunEnt_model_dp = NULL;
    }
}
