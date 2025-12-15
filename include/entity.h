#ifndef __entity_H__
#define __entity_H__

#include "defs.h"
#include <t3d/t3d.h>
#include <t3d/t3dmath.h>
#include <t3d/t3dmodel.h>
#include <libdragon.h>

typedef struct entity_S {
    u8 _inUse;
    u8 billboard;
    u8 visible;
    u8 padding;
    u32 state;
    T3DVec3 position;
    T3DVec3 rotation;
    T3DVec3 scale;
    struct entity_S* parent;
    struct entity_S* child;
    rspq_block_t* model;
    T3DMat4FP model_mat;

    void (*update)(struct entity_S*);
    void (*think)(struct entity_S*);
    void (*collide)(struct entity_S*, struct entity_S*);

} entity;

void entity_init(int);
void entity_cleanup();

entity* entity_new();
void entity_free(entity*);

void entity_think_all();
void entity_update_all();
void entity_draw_all();

#endif