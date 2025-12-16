#include <camera.h>
#include <entity.h>

static T3DVec3 camera_position_max_radial = {{0,50.0f,0}};
static T3DVec3 camera_position = {{0,50.0f,0}};
static T3DVec3 camera_target = {{0.0f,0.0f,0}};
static float view_angle = 0.0f;
static float max_radial_distance = 250.0f;
static float zoom = 0.1f;

static entity* target_entity = NULL;

T3DVec3* get_camera_position(){ return &camera_position; }
T3DVec3* get_camera_target() { return &camera_target; }

void camera_set_target(entity* target){
    target_entity = target;
}

void camera_update(joypad_inputs_t* joypad){
    view_angle += joypad->stick_x * 0.0001f;
    zoom = fmin(fmax(zoom - (joypad->stick_y * 0.0001f), 0.1f), 1.0f);

    if(target_entity != NULL){
        camera_target.x = target_entity->position.x;
        camera_target.z = target_entity->position.z;
    }

    camera_position_max_radial.x = camera_target.x + cos(view_angle) * max_radial_distance;
    camera_position_max_radial.z = camera_target.z + sin(view_angle) * max_radial_distance;

    float dist = t3d_vec3_distance(&camera_target, &camera_position_max_radial);
    camera_position.x = ((camera_position_max_radial.x - camera_target.x) * (dist * (zoom * 0.01f)));
    camera_position.y = ((camera_position_max_radial.y - camera_target.y) * (dist * (zoom * 0.01f)));
    camera_position.z = ((camera_position_max_radial.z - camera_target.z) * (dist * (zoom * 0.01f)));
    
}

void camera_debug(){
    rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, 5, 15, "View Angle: %f", view_angle);
    rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, 5, 27, "Zoom: %f", zoom);
}