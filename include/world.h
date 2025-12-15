#ifndef __world_H__
#define __world_H__
#include <entity.h>

entity* world_new();
void world_free(entity* self);

#endif