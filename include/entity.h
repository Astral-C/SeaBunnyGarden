#ifndef __entity_H__
#define __entity_H__

#include "defs.h"
#include <libdragon.h>
#include <t3d/t3d.h>
#include <t3d/t3dmath.h>
#include <t3d/t3dmodel.h>

typedef struct entity {
    u8 _inUse;
    u8 billboard;
    u8 visible;
    u8 padding;
    u32 state;
    u32 health;
    T3DVec3 position;
    T3DVec3 rotation;
    T3DVec3 scale;
    float direction;
    float speed;
    struct entity* parent;
    struct entity* child;
    rspq_block_t* model;
    T3DMat4FP model_mat;

    void (*update)(struct entity*);
    void (*think)(struct entity*);
    void (*collide)(struct entity*, struct entity*);

} entity;

void entity_init(int);
void entity_cleanup();

entity* entity_new();
void entity_free(entity*);

void entity_think_all();
void entity_update_all();
void entity_draw_all();

#endif