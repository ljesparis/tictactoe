#include <stdio.h>
#include <string.h>

#include "map.h"
#include "player.h"
#include "ai.h"
#include "log.h"

#define CLEAR_SCREEN printf("\e[1;1H\e[2J")

static uint8_t x_counter = 0, o_counter = 0;

#define RESET_COUNTERS \
    x_counter = 0;     \
    o_counter = 0;

#define INCREMENT_COUNTERS(raw_player) \
    switch (raw_player)                \
    {                                  \
    case X_PLAYER:                     \
        x_counter++;                   \
        break;                         \
                                       \
    case O_PLAYER:                     \
        o_counter++;                   \
        break;                         \
    }

#define WINNER                                                  \
    x_counter == ROWS ? X_PLAYER : o_counter == ROWS ? O_PLAYER \
                                                     : UNKOWN_PLAYER

#define RENDER_MAP(map) \
    CLEAR_SCREEN;       \
    render((const struct map_t *)map);

#define CHECK_FOR_WINNER_OR_TIED_GAME(game_map)                             \
    {                                                                       \
        uint8_t raw_player_winner = UNKOWN_PLAYER;                          \
        if ((raw_player_winner = lookup_winner(game_map)) != UNKOWN_PLAYER) \
        {                                                                   \
            printf("The winner is '%c'.\n", raw_player_winner);             \
            exit(0);                                                        \
        }                                                                   \
                                                                            \
        if (is_tied_game(game_map) == 0)                                    \
        {                                                                   \
            printf("TIED GAME!\n");                                         \
            exit(0);                                                        \
        }                                                                   \
    }

typedef uint8_t (*Move)(const struct map_t *map);

int8_t is_tied_game(const struct map_t *map)
{
    uint8_t len = map->rows * map->columns, j = 0;
    for (int8_t i = 0; i < len; i++)
    {
        if (IS_PLAYER_VALID(*(map->raw_map + i)))
        {
            j++;
        }
    }
    return j == len ? 0 : -1;
}

uint8_t lookup_winner(const struct map_t *map)
{
    // First loop:
    // Search a winner in horizontal lines.
    for (uint8_t i = 1; i <= map->rows * map->columns; i++)
    {
        INCREMENT_COUNTERS(*(map->raw_map + i - 1));
        if (WINNER != UNKOWN_PLAYER)
        {
            goto ret;
        }

        if (i % map->rows == 0)
        {
            RESET_COUNTERS
        }
    }

    // Second loop:
    // Search a winner in vertical lines.
    for (uint8_t i = 0; i < map->columns; i++)
    {
        RESET_COUNTERS

        for (uint8_t j = 0, m = 0; j < map->rows; j++, m = m + map->rows)
        {
            INCREMENT_COUNTERS(*(map->raw_map + i + m));

            if (WINNER != UNKOWN_PLAYER)
            {
                goto ret;
            }
        }
    }

    RESET_COUNTERS

    // Third loop:
    // Search a winner in slanting lines.
    // Part 1.
    //
    //  | X | - | - |
    //  | - | X | - |
    //  | - | - | X |
    //
    for (uint8_t i = 0; i < map->rows * map->columns; i = i + map->rows + 1)
    {
        INCREMENT_COUNTERS(*(map->raw_map + i));

        if (WINNER != UNKOWN_PLAYER)
        {
            goto ret;
        }
    }

    RESET_COUNTERS

    // Part 2.
    //
    //  | - | - | X |
    //  | - | X | - |
    //  | X | - | - |
    //
    for (uint8_t i = (map->rows * map->columns) - map->rows; i > 0; i = i - map->rows + 1)
    {
        INCREMENT_COUNTERS(*(map->raw_map + i));

        if (WINNER != UNKOWN_PLAYER)
        {
            goto ret;
        }
    }

    RESET_COUNTERS

ret:
    return WINNER;
}

int main(void)
{
    if (ROWS != COLUMNS)
    {
        ERROR("Rows and Columns should have the same size.");
    }

    struct player_t **players = choose_players();
    struct player_t *user_player = USER_PLAYER(players);
    struct player_t *machine_player = MACHINE_PLAYER(players);

    struct map_t *game_map = default_map();

    RENDER_MAP(game_map);

    Move second_player_move = NULL, main_player_move = NULL;
    struct player_t *main_player = NULL, *second_player = NULL;

    for (;;)
    {
        if (user_player->i_play_first)
        {
            main_player_move = get_user_move, second_player_move = get_machine_move;
            main_player = user_player, second_player = machine_player;
        }
        else
        {
            main_player_move = get_machine_move, second_player_move = get_user_move;
            main_player = machine_player, second_player = user_player;
        }

        set_play(game_map, main_player, main_player_move(game_map));

        RENDER_MAP(game_map);
        CHECK_FOR_WINNER_OR_TIED_GAME(game_map);

        set_play(game_map, second_player, second_player_move(game_map));

        RENDER_MAP(game_map);
        CHECK_FOR_WINNER_OR_TIED_GAME(game_map);
    }

    free_player_arr(players);
    free_map(game_map);

    return 0;
}