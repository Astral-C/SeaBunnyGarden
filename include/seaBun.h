#ifndef __seaBun_H__
#define __seaBun_H__
#include <entity.h>

typedef struct seaBun_S {
    u8 _inUse;
    u8 hat;
    u8 location;
    u8 lvl_stat;
    u8 strength_stat;
    u8 speed_stat;
    entity* seaBunEnt;
} seaBun;

void SeaBun_init(int);
void SeaBun_cleanup();

seaBun* SeaBun_new();
void SeaBun_free(seaBun* self);

#endif
