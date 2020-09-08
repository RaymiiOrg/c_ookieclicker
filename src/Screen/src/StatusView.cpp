//
// Created by remy on 08-09-20.
//

#include "StatusView.h"
#include <iostream>

void StatusView::render() {
    std::cout << "StatusView" << std::endl;
}

void StatusView::handleInput(const std::string &input) {

}

StatusView::StatusView(Wallet &wallet) : wallet(wallet) {

}
