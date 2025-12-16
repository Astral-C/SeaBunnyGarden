#ifndef __util_H__
#define __util_H__

#include <libdragon.h>
#include <t3d/t3d.h>
#include <t3d/t3dmath.h>
#include <t3d/t3dmodel.h>

void free_dp_deferred(void* block);

float get_time_s();
float get_time_ms();

#endif