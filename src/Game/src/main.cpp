#include "GameLoop.h"
#include <memory>

int main() {
    std::cout << escapeCode.hideCursor << escapeCode.clearEntireScreen << escapeCode.placeCursorAt1x1;
    auto thisGame = std::make_unique<Gameloop>();
    return 0;
}

