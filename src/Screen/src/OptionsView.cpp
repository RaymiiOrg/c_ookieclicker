//
// Created by remy on 08-09-20.
//

#include <CookieNumbers.h>
#include "OptionsView.h"

void OptionsView::render() {
    std::cout << "\n===== Options ====\n";

    std::cout << "[q]: quit; \n";
    std::cout << "[s]: save; \n";
    std::cout << "[l]: load; \n";
    std::cout << std::endl;
    std::cout << "version: " << game::gameVersion << std::endl;
}

void OptionsView::handleInput(const std::string &input) {

}
