#include "Game.h"

int main()
{
    auto game = CreateGame();
    game->run();
    delete game;
    return 0;
}
