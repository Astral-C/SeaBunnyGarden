#ifndef __gamestate_H__
#define __gamestate_H__

typedef struct state_S {
    void (*draw_3d)(struct state_S*);
    void (*draw_2d)(struct state_S*);
    void (*update)(struct state_S*);
    void (*enter)(struct state_S*);
    void (*exit)(struct state_S*);
    void (*transition_enter)(struct state_S*);
    void (*transition_exit)(struct state_S*);
    float transition_speed;
    float transition_time;
    void* data;
} gamestate;

struct States {
    gamestate main_menu;
    gamestate main;
};

extern struct States GameStates;

int in_state_transition();
void set_initial_sate(gamestate* s);
void cleanup_state();
void update_gamestate();
void draw_gamestate_3d();
void draw_gamestate_2d();
void switch_gamestate(gamestate* s);

#endif