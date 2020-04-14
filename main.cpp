#include "Game.h"
#include <memory>
#include <zconf.h>

int main() {
    auto thisGame = std::make_unique<Game>();

    thisGame->start();
    while(!thisGame->isFinished()) {
         thisGame->next_iteration();
    }
    return 0;
}

