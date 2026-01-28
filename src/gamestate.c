#include <gamestate.h>
#include <tidepool.h>
#include <menus.h>
#include <garden.h>

static gamestate* current_state = NULL;
static gamestate* target_state = NULL;

static bool transitioning_state_exit = false;
static bool transitioning_state_enter = false;
static float transition_time_remaining = 0.0f;

void test_enter(gamestate* s){
}
void test_exit(gamestate* s){}

struct States GameStates = {
    .main_menu = {
        .draw_2d = main_menu_draw_2d,
        .draw_3d = main_menu_draw_3d,
        .update = main_menu_update,
        .enter = main_menu_enter,
        .exit = main_menu_exit,
        .transition_enter = test_enter,
        .transition_exit = test_exit,
        .transition_time = 0.0f,
        .transition_speed = 0.05f,
        .data = NULL
    },
    .main = {
        .draw_2d = tidepool_draw_2d,
        .draw_3d = tidepool_draw_3d,
        .update = tidepool_update,
        .enter = tidepool_enter,
        .exit = tidepool_exit,
        .transition_enter = test_enter,
        .transition_exit = test_exit,
        .transition_time = 0.0f,
        .transition_speed = 0.05f,
        .data = NULL
    },
    .garden = {
        .draw_2d = tidepool_draw_2d,
        .draw_3d = tidepool_draw_3d,
        .update = tidepool_update,
        .enter = tidepool_enter,
        .exit = tidepool_exit,
        .transition_enter = test_enter,
        .transition_exit = test_exit,
        .transition_time = 0.0f,
        .transition_speed = 0.05f,
        .data = NULL
        /*.draw_2d = garden_draw_2d,
        .draw_3d = garden_draw_3d,
        .update = garden_update,
        .enter = garden_enter,
        .exit = garden_exit,
        .transition_enter = test_enter,
        .transition_exit = test_exit,
        .transition_time = 0.0f,
        .transition_speed = 0.05f,
        .data = NULL*/
    }
};

int in_state_transition() {
    return transitioning_state_exit + transitioning_state_enter;
}

void set_initial_state(gamestate* s){
    current_state = s;
    current_state->enter(current_state);
}

void cleanup_state(){
    current_state->exit(current_state);
}

void draw_gamestate_2d(){
    current_state->draw_2d(current_state);
}

void draw_gamestate_3d(){
    current_state->draw_3d(current_state);
}

void update_gamestate(){
    if(transitioning_state_exit){
        if(transition_time_remaining <= 0.0f){
            transition_time_remaining = 0.0f;
            
            if(current_state->exit) current_state->exit(current_state);
            
            current_state = target_state;
            target_state = NULL;

            if(current_state->enter) current_state->enter(current_state);

            transitioning_state_exit = false;
            if(current_state->transition_enter != NULL) transitioning_state_enter = true;
        } else {
            current_state->transition_exit(current_state);
            transition_time_remaining -= current_state->transition_speed;
        }
    } else if(transitioning_state_enter) {
        if(transition_time_remaining <= 0.0f){
            transition_time_remaining = 0.0f;

            transitioning_state_enter = false;
        } else {
            current_state->transition_enter(current_state);
            transition_time_remaining -= current_state->transition_speed;
        }
    } else {
        current_state->update(current_state);
    }
}

void switch_gamestate(gamestate* s){
    if(current_state->transition_exit){
        transitioning_state_exit = true;
    } else if(current_state->transition_enter){
        transitioning_state_enter = true;
    }
    
    if(current_state->transition_exit || current_state->transition_enter) {
        transition_time_remaining = current_state->transition_time;
        target_state = s;
    } else {
        current_state = s;
    }
}