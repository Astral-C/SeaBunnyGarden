#include <camera.h>
#include <entity.h>

static T3DVec3 camera_position = {{250.0f,50.0f,0}};
static T3DVec3 camera_target = {{0.0f,0.0f,0}};
static float view_angle = 0.0f;
static entity* target_entity = NULL;

T3DVec3* get_camera_position(){ return &camera_position; }
T3DVec3* get_camera_target() { return &camera_target; }

void camera_set_target(entity* target){
    target_entity = target;
}

void camera_update(joypad_inputs_t* joypad){
    view_angle += joypad->stick_x * 0.0001f;

    if(target_entity != NULL){
        camera_target.x = target_entity->position.x;
        camera_target.z = target_entity->position.z;
    }

    camera_position.x = camera_target.x + cos(view_angle)*250.0f;
    camera_position.z = camera_target.z + sin(view_angle)*250.0f;
    
}

void camera_debug(){
    rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, 5, 15, "View Angle: %f", view_angle);
}