//
// Created by remy on 08-09-20.
//

#include "StatusView.h"
#include "terminalCodes.h"
#include <iostream>

void StatusView::render() {
    std::cout << escapeCode.eraseCurrentLine;
    std::cout << "Cookies\t:\t";
    if (wallet != nullptr && wallet->getCookieAmount() > 0)
        std::cout << cp.print(wallet->getCookieAmount());
    std::cout << std::endl;
    std::cout << escapeCode.eraseCurrentLine;
    std::cout << "cps\t:\t";
    if (wallet != nullptr && wallet->getCps() > 0)
        std::cout << cp.print(wallet->getCps());
    std::cout << std::endl;
    std::cout << escapeCode.eraseCurrentLine;
}

void StatusView::handleInput(const std::string &input) {

}
