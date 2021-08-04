# Version 106 - current development

Release date: 2020-

New features:

- Building upgrades
- Debian package available
- Boost libraries are now a compile option (otherwise an unsigned long long / long double is used, including overflow)

Improvements

- Added Cookies via Input Achievement
- CMake has project and version info
- CMake main game is renamed from "Game" to "c_ookieclicker"
- CMake links to threads in a platform agnostic way

Bug fixes

- 

The savegame format has been updated to version 2 for this release.

# Version 105

Release date: 2020-09-19

Big new feature:

- Implemented first two types of Achievement: `Cookie Amount achievements` 
  & `Cookies per Second achievements`.
  - Experimenting with the Observer design pattern for this one:
    added observer pattern style notifications on Wallet->incrementCookieAmount

Improvements: 
- Moved over construction of objects to main.cpp, now
  better dependency injection.
- Removed screen rendering code from
  main game loop into its own View class,
  each `View` can have one or more `Views`,
  each view has at least a `render()` and `handleInput()`
  method. Views could have views as wel, as subviews.
- Display Cookienumbers more like javascript game, 
  with some numbers behind the comma.
- Added coding style check (clang-format)

Bug fixes:

- Fix segfault when threading went haywire on starting.
- Fix crash when loading savegame with space in its name.  


# Version 104

Release date: 2020-07-12

- Refactored price increase formula to match original javascript game
- Matches items, prices and cps with Javascript game
- Performance optimization for item price calculation (1/10/100)
- Events print seconds
- Multiple input charactes allowed (ex: cc gets 2 cookies)
- Refactored cookienumber to be a `cpp_dec_float` instead of int to allow for `0.1`
  cookies per second.

# Version 103

Release date:  

- Implemented save game function
  - Allows game to be saved with `s` and if 
    a save file is found in the current folder,
    loaded with `l`.
- Changed inventory no not hold `Item&` but just `std::string`
- Fix static compilation by including the whole pthread library (`--whole-archive`)

# Version 102

Release date: 2020-05-30.

- Added input tab bar to make display less cluttered
  - 1 = itemstore to buy one item;
  - 2 = itemstore to buy the max amount items that your current cookie count allows
  - 3 = show inventory
  - 4 = show achievements (not built yet)
- Changed cookies per tap (`c` cursor) to be dynamic (default one) in preparation of achievements.

# Version 101

Release date: 2020-05-24.

- Added cookienumber printing in format used by other incremental games. 
  - Example: `1000000000000000000000` becomes `1 sextillion`. 
  - Example: `21341831944003682716936974836612280224172215802627435299099076055022090949593824685640853139456777002501904985670414671748540291630152113086259344562839841917575524836560787544358350755299402239335813148535474932165751` becomes `21xx`.

# Version 100

Release date: 2020-05-23.

- Use boost::multiprecision for most numbers
- Added price increment to items when bought
- Added version number

# Version 99

Release date: 2020-04-07.

Initial version of the game. Following features implemented:

- Commandline interface
- Thread for user input
- Thread for game logic
- Inventory system
- Cookie increment based on cps
