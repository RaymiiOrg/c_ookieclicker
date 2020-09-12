#include "GameLoop.h"
#include <memory>

int main()
{
    std::cout << escapeCode.hideCursor << escapeCode.clearEntireScreen << escapeCode.cursorTo1x1;
    auto game = std::make_unique<Gameloop>();
    std::cout << escapeCode.showCursor;
    return 0;
}
