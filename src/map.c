#include "map.h"
#include "player.h"
#include "log.h"

struct map_t *create_map(const uint8_t columns, const uint8_t rows)
{
    struct map_t *map = (struct map_t *)malloc(sizeof(struct map_t *));
    map->rows = rows;
    map->columns = columns;
    map->raw_map = (uint8_t *)malloc(rows * columns);

    for (uint8_t i = 0; i < (rows * columns); i++)
    {
        *(map->raw_map + i) = FROM_INTEGER_TO_ASCII_INTEGER(i);
    }

    return map;
}

struct map_t *default_map()
{
    return create_map(COLUMNS, ROWS);
}

void render(const struct map_t *m)
{
    for (uint8_t i = 1; i <= m->rows * m->columns; i++)
    {
        printf("| %c ", *(m->raw_map + i - 1));
        if (!(i % m->columns))
        {
            printf("|\n");
        }
    }
}

void free_map(struct map_t *m)
{
    m->columns = 0;
    m->rows = 0;

    if (m->raw_map != NULL)
    {
        free((void *)m->raw_map);
        m->raw_map = NULL;
        ASSERT(m->raw_map == NULL, "Raw map released.");
    }

    free((void *)m);
    m = NULL;
    ASSERT(m == NULL, "Map released.");
}

uint8_t set_play(struct map_t *m, const struct player_t *player, const int8_t pos)
{
    uint8_t c = *(m->raw_map + pos);
    if (c != X_PLAYER && c != O_PLAYER)
    {
        *(m->raw_map + pos) = player->raw_player;
        return 0;
    }

    return -1;
}
