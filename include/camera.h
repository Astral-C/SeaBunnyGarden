#ifndef __camera_H__
#define __camera_H__
#include <libdragon.h>

#include <t3d/t3d.h>
#include <t3d/t3dmath.h>

T3DVec3* get_camera_position();
T3DVec3* get_camera_target();

void camera_update(joypad_inputs_t* joypad);
void camera_debug();

#endif