#include "ai.h"
#include "map.h"
#include "player.h"

#include <time.h>

#define MAX_RETRY 100

uint8_t get_machine_move(const struct map_t *map)
{
    /**
     * Dummy AI =P.
     * */

    srand(time(NULL));

    uint8_t pos = UNKOWN_PLAYER, slot_content = 0, retry = 0;
    for (;;)
    {
        pos = rand() % (map->columns * map->rows);
        slot_content = *(map->raw_map + pos);
        if (!(IS_PLAYER_VALID(slot_content)))
        {
            break;
        }

        if (retry++ == MAX_RETRY)
        {
            break;
        }
    }

    return pos;
}