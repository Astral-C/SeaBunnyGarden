#ifndef __entity_H__
#define __entity_H__

#include "defs.h"
#include <t3d/t3d.h>
#include <t3d/t3dmath.h>
#include <t3d/t3dmodel.h>
#include <libdragon.h>

typedef struct Entity_S {
    u8 _inUse;
    u32 state;
    T3DVec3 position;
    T3DVec3 rotation;
    T3DVec3 scale;
    struct Entity_S* parent;
    struct Entity_S* child;
    T3DModel* model;
    T3DMat4FP modelMat;

    void (*update)(struct Entity_S*);
    void (*think)(struct Entity_S*);
    void (*collide)(struct Entity_S*, struct Entity_S*);

} Entity;

void InitEntities(int);
void FreeEntities();

Entity* NewEntity();
void FreeEntity(Entity*);

#endif