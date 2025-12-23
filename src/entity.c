#include <entity.h>
#include <camera.h>

static entity* entities = NULL;
static u32 entityCount = 0;

void entity_init(int count){
    entities = (entity*)malloc_uncached(sizeof(entity)*count);
    entityCount = count;
    memset(entities, 0, sizeof(entity)*count);
}

void entity_cleanup(){
    free_uncached(entities);
}

void entity_think_all(){
    for(int i = 0; i < entityCount; i++){
        if(!entities[i]._inUse || entities[i].think == NULL) continue;
        entities[i].think(&entities[i]);
    }
}

void entity_update_all(){
    for(int i = 0; i < entityCount; i++){
        if(!entities[i]._inUse || entities[i].update == NULL) continue;
        entities[i].update(&entities[i]);
    }
}

void entity_draw_all(){
    for(int i = 0; i < entityCount; i++){
        if(!entities[i]._inUse || !entities[i].visible || entities[i].model == NULL) continue;
        if(entities[i].billboard){
            T3DMat4 m;
            t3d_mat4_look_at(&m, &entities[i].position, get_camera_position(), &(T3DVec3){{0,1,0}});
            t3d_mat4_to_fixed_3x4(&entities[i].model_mat, &m);
        } else {
            t3d_mat4fp_from_srt_euler(&entities[i].model_mat, entities[i].scale.v, entities[i].rotation.v, entities[i].position.v);
        }
        t3d_matrix_set(&entities[i].model_mat, true);
        rspq_block_run(entities[i].model);
    }
}

entity* entity_new(){
    for(int i = 0; i < entityCount; i++){
        if(!entities[i]._inUse){
            entities[i]._inUse = 1;
            entities[i].visible = 1;
            entities[i].billboard = 0;
            entities[i].scale.x = 1.0f;
            entities[i].scale.y = 1.0f;
            entities[i].scale.z = 1.0f;
            return &entities[i];
        }
    }
    return NULL;
}

void entity_free(entity* e){
    if(e == NULL) return;
    e->_inUse = 0;
    e->model = NULL;
}