#ifndef _AI_H_
#define _AI_H_

#include <stdlib.h>

struct map_t;

uint8_t get_machine_move(const struct map_t *map);

#endif // _AI_H_