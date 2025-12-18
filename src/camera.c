#include <camera.h>
#include <entity.h>

static T3DVec3 camera_position_max = {{0.0f, 50.0f, 250.0f}};
static T3DVec3 camera_position = {{0.0f, 50.0f, 250.0f}};
static T3DVec3 camera_target = {{0.0f, 0.0f, 0.0f}};
static float zoom = 0.1f;

static entity* target_entity = NULL;

T3DVec3* get_camera_position(){ return &camera_position; }
T3DVec3* get_camera_target() { return &camera_target; }

void camera_set_target(entity* target){
    target_entity = target;
    if(target == NULL){
        camera_target = (T3DVec3){{0.0f, 0.0f, 0.0f}};
        camera_position = (T3DVec3){{0.0f, 50.0f, 250.0f}};
    }
}

void camera_update(joypad_inputs_t* joypad){
    camera_position.x += joypad->stick_x * 0.1f;
    camera_target.x = camera_position.x;
    zoom = fmin(fmax(zoom - (joypad->stick_y * 0.0001f), 0.1f), 1.0f);

    if(target_entity != NULL){
        camera_target.x = target_entity->position.x;
        camera_target.z = target_entity->position.z;
        camera_position.x = camera_target.x;
        camera_position.z = (camera_target.z - 250.0f) * zoom;
    } else {
        camera_target.z += (joypad->stick_y * 0.1f);
        camera_position.z += (joypad->stick_y * 0.1f);
    }
    
    
}

void camera_debug(){
    rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, 5, 15, "View X: %f", camera_position_max.x);
    rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, 5, 27, "Zoom: %f", zoom);
}