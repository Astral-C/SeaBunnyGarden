#include <entity.h>

static Entity* entities = NULL;
static u32 entityCount = 0;

void InitEntities(int count){
    entities = (Entity*)malloc_uncached(sizeof(Entity)*count);
    entityCount = count;
    memset(entities, 0, sizeof(Entity)*count);
}

void FreeEntities(){
    free_uncached(entities);
}

Entity* NewEntity(){
    for(int i = 0; i < entityCount; i++){
        if(!entities[i]._inUse){
            entities[i]._inUse = 1;
            return &entities[i];
        }
    }
}

void FreeEntity(Entity* e){
    e->_inUse = 0;
    e->model = NULL;
}