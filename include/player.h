#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <stdlib.h>
#include <stdio.h>

#define X_PLAYER 'X'
#define O_PLAYER 'O'
#define UNKOWN_PLAYER '\0'
#define MAX_PLAYERS 2
#define PLAYER_T_SIZE sizeof(struct player_t *)
#define IS_PLAYER_VALID(c) c == X_PLAYER || c == O_PLAYER
#define USER_PLAYER(player_arr_ptr) *(player_arr_ptr + 0 * PLAYER_T_SIZE)
#define MACHINE_PLAYER(player_arr_ptr) *(player_arr_ptr + 1 * PLAYER_T_SIZE)

struct player_t
{
    uint8_t raw_player, i_play_first;
};

struct map_t;

struct player_t *create_player(const uint8_t raw);
void free_player(struct player_t **player);
void free_player_arr(struct player_t **players);
struct player_t **choose_players();
uint8_t get_user_move(const struct map_t *map);

#endif // _PLAYER_H_