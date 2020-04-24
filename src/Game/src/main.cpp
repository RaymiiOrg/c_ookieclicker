#include "GameLoop.h"
#include <memory>

int main() {

//    auto thisGame = std::make_unique<Game>();
//    thisGame->start();
//    while(!thisGame->isFinished()) {
//         thisGame->next_iteration();
//    }
    std::cout << escapeCode.hideCursor << escapeCode.clearEntireScreen << escapeCode.placeCursorAt1x1;
    auto thisGame = std::make_unique<Gameloop>();
    return 0;
}

