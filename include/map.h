#ifndef _MAP_H_
#define _MAP_H_

#include <stdlib.h>
#include <stdio.h>

#define ROWS 3
#define COLUMNS 3
#define FROM_INTEGER_TO_ASCII_INTEGER(c) c + 48
#define FROM_ASCII_INTEGER_TO_INTEGER(c) c - 48

struct player_t;

struct map_t
{
    uint8_t rows, columns, *raw_map;
};

struct map_t *create_map(const uint8_t columns, const uint8_t rows);
struct map_t *default_map();
void render(const struct map_t *m);
uint8_t set_play(struct map_t *m, const struct player_t *player, const int8_t pos);
void free_map(struct map_t *m);

#endif // _MAP_H_