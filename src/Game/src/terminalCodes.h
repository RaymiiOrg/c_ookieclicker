//
// Created by remy on 08-09-20.
//

#ifndef C_OOKIECLIKER_TERMINALCODES_H
#define C_OOKIECLIKER_TERMINALCODES_H
#include <string>

/* ANSII escape codes for the terminal */
struct escapeCodes {
    const std::string hideCursor {"\033[?25l"};
    const std::string clearEntireScreen {"\033[2J"};
    const std::string placeCursorAt1x1 {"\033[1;1H"};
    const std::string cursorUpOneLine {"\033[A"};
    const std::string cursorDownOneLine {"\033[B"};
    const std::string eraseCurrentLine {"\033[2K"};
    const std::string cursorToBeginningOfLine {"\r"};
    const std::string terminalBold {"\033[1m"};
    const std::string terminalReset {"\033[0m"};
    const std::string terminalUnderline {"\033[4m"};
    const std::string terminalDim {"\033[2m"};
    const std::string cursorTo0x0 {"\033[0;0f"};
    const std::string cursorTo7x0 {"\033[7;0f"};
};

/* global variable holding the escapecodes */
static const escapeCodes escapeCode;

#endif //C_OOKIECLIKER_TERMINALCODES_H
