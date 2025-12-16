#include <util.h>

void free_dp_deferred(void* block){
    rspq_block_free(block);
}

float get_time_s()  { return (float)((double)get_ticks_ms() / 1000.0); }
float get_time_ms() { return (float)((double)get_ticks_us() / 1000.0); }