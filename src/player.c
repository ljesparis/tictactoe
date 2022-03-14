#include "player.h"
#include "map.h"
#include "log.h"

struct player_t *create_player(const uint8_t raw)
{
    struct player_t *player = (struct player_t *)malloc(PLAYER_T_SIZE);
    player->raw_player = raw;
    player->i_play_first = raw == X_PLAYER;
    return player;
}

void free_player(struct player_t **player)
{
    (*player)->i_play_first = 0;
    (*player)->raw_player = 0;
    if ((*player) != NULL)
    {
        free((void *)(*player));
        (*player) = NULL;
    }
}

void free_player_arr(struct player_t **players)
{
    uint8_t index = 0;
    do
    {
        struct player_t *player = *(players + (index * PLAYER_T_SIZE));
        free_player(&player);
        ASSERT(player == NULL, "Player released.");
    } while (++index < MAX_PLAYERS);

    free((void *)players);
    players = NULL;
    ASSERT(players == NULL, "Players array releared.");
}

struct player_t **choose_players()
{

    uint8_t raw_player;
    for (;;)
    {
        printf("What player would you choose, 'X' or 'O' ? ");
        raw_player = getc(stdin);
        if (IS_PLAYER_VALID(raw_player))
        {
            break;
        }

        printf("Please, try again.\n");
    }

    fflush(stdin);

    struct player_t *user_player = NULL;
    struct player_t *machine_player = NULL;
    if (raw_player == X_PLAYER)
    {
        user_player = create_player(raw_player);
        machine_player = create_player(O_PLAYER);
    }
    else
    {
        machine_player = create_player(X_PLAYER);
        user_player = create_player(raw_player);
    }

    struct player_t **players = (struct player_t **)malloc(MAX_PLAYERS * PLAYER_T_SIZE);
    *(players + 0 * PLAYER_T_SIZE) = user_player;
    *(players + 1 * PLAYER_T_SIZE) = machine_player;
    return players;
}

uint8_t get_user_move(const struct map_t *map)
{
    uint8_t pos;
    uint8_t map_length = ((map->columns * map->rows) - 1);

    for (;;)
    {
        printf("Please, select position: ");
        pos = getc(stdin);
        pos = FROM_ASCII_INTEGER_TO_INTEGER(pos);

        fflush(stdin);

        if (pos > map_length)
        {
            printf("This position does not exists. Please, try again.\n");
            continue;
        }

        uint8_t slot_content = *(map->raw_map + pos);
        if (IS_PLAYER_VALID(slot_content))
        {
            printf("The slot '%d' is occupied by '%c'. Please try again.\n", pos, slot_content);
        }
        else
        {
            break;
        }
    }

    return pos;
}
