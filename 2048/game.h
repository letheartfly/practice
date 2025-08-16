#ifndef GAME_H
#define GAME_H

#include "myhead.h"

typedef struct GameState
{
    int map[4][4];
    long long score;
}GameState;

void init_game(GameState *game_state);
void print_state(GameState *game_state);
bool get_operator(char *input, char *operator, int size);
void playing(GameState *game_state);
bool check_win(GameState *game_state);
bool check_blank(GameState *game_state);
void spawn_tile(GameState *game_state);
bool game_over(GameState *game_state);
bool move_up(GameState *game_state);
bool move_left(GameState *game_state);
bool move_right(GameState *game_state);
bool move_down(GameState *game_state);

// 生成新数字（90%生成2，10%生成4）
static inline int gener_num()
{
    return (rand() % 100 < 90) ? 2 : 4;
}

#endif