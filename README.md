# c_ookieclicker

![C/C++ CI](https://github.com/RaymiiOrg/c_ookieclicker/workflows/C/C++%20CI/badge.svg)

![demo.gif][2]

c_ookieclicker is my personal pet project to experiment with c++. It is a clone of the famour
cookieclicker game [by ortiel][1]. A clone of a game is simple enough to get up and running fairly quickly, but also extensible enough when needed. How do you store huge score numbers when they don't fit in a `long long`? How do you write a game loop, how to use threads to handle user input? Saving a game (how to design a proper save format)? Also a great way to learn about project organization, software architecture and to try out design patterns.


# Build

How to build the game for yourself.

Install `boost` and build dependencies. On Ubuntu:

    sudo apt install libboost-dev-all build-essential cmake
 
Clone the repository:

    git clone https://github.com/RaymiiOrg/c_ookieclicker/
    
Build locally: 

    mkdir build
    cmake -Bbuild -H.
    cmake --build build/ --target all 
    # or old fashioned:
    # cd build
    # cmake ..
    # make
    
The game executable is:

    src/Game/src/Game.exe
 

# Different parts of the game

## CookieNumber

Class which allows storing of a large number (score, prices, inventory amount). Currently a typedef alias to Boosts multiprecision cpp_int.  
 
Supports printing in format used by other incremental games. 
  - Example: `1000000000000000000000` becomes `1 sextillion`. 
  - Example: `21341831944003682716936974836612280224172215802627435299099076055022090949593824685640853139456777002501904985670414671748540291630152113086259344562839841917575524836560787544358350755299402239335813148535474932165751` becomes `21xx`.

The printing method is quite inefficient. It consists of multiple if statements.

## Inventory

### Items

The same from the original game.

- Cursors
- Grandmas
- Farms
- Mines
- Factories
- Banks
- Temples
- Wizard towers
- Shipments
- Alchemy labs
- Portals
- Time machines
- Antimatter condensers
- Prisms
- Chancemakers
- Fractal Engines
- Javascript Consoles

## Achievements



## Wallet

## Store

## Game loop

### Game step

### User input


## User interface


## Savegame

The game is saved in your current folder, filename is `.cookieclicker.save`. Text based format, field seperated
by a `;`. Don't manually edit the file or you might loose your savegame.

[1]: https://orteil.dashnet.org/cookieclicker/
[2]: demo4.gif