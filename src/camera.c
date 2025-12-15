#include <camera.h>

static T3DVec3 camera_position = {{250.0f,250.0f,0}};
static T3DVec3 camera_target = {{0.0f,0.0f,0}};

T3DVec3* get_camera_position(){ return &camera_position; }
T3DVec3* get_camera_target() { return &camera_target; }