#include "game.h"

int main()
{
    GameState game_state = {0};
    init_game(&game_state);
    playing(&game_state);
    return 0;
}