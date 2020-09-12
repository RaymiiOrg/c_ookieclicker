# c_ookieclicker

<a href="https://github.com/RaymiiOrg/c_ookieclicker/actions"><img src="https://github.com/RaymiiOrg/c_ookieclicker/workflows/C/C++%20CI/badge.svg" alt="ci badge"></a>

![demo.gif][2]

[More (1)][3] [screenshots (2)][4] [here (3)][5].

c_ookieclicker is my personal pet project to experiment with c++. It is a clone of the famous 
cookieclicker game [by ortiel][1]. A clone of a game is simple enough to get up and running 
fairly quickly, but also extensible enough when needed. How do you store huge score numbers 
when they don't fit in a `long long`? How do you write a game loop, how to use threads to handle 
user input? Saving a game (how to design a proper save format)? Also a great way to learn about 
project organization, software architecture and to try out design patterns.


# How to play

Release binaries can be found in the `releases` folder. The latest release will
always be the current development version, which is unstable at best.  

Either download a release binary or clone the git repo and build yourself.

Start up the game. In the top you'll see your amount of cookies and
your Cookies per Second. Press `c`, then `Enter` to bake your first 
cookie. Repeat until you can buy items (like a cursor or grandma)
to automate your baking. There is no end to the game, but main goal
is to automate as much as possible. 


# License

GNU gpl v2.

# Build

How to build the game for yourself.

Install `boost` and build dependencies. On Ubuntu 18.04:

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

    src/Game/src/Game_linux
    
Make sure to run it in the cloned folder, otherwise some game data might not load, like
then achievements. Game data files are in:
    
    releases/$version/gamedata
    
and are symlinked in the main folder you cloned from github.


# Different parts of the game

## CookieNumber

Class which allows storing of a large number (score, prices, inventory amount). 
Currently a typedef alias to Boosts multiprecision `cpp_dec_float`.  
 
Supports printing in format used by other incremental games. 
  - Example: `1000000000000000000000` becomes `1 sextillion`. 
  - Example: `21341831944003682716936974836612280224172215802627435299099076055022090949593824685640853139456777002501904985670414671748540291630152113086259344562839841917575524836560787544358350755299402239335813148535474932165751` becomes `21xx`.

Look at the `CookieNumberPrinter` class how I print in the incremental / idle game style. 

## CookieInt

typedef to a Boost multiprecision `cpp_int`. Same as CookieNumber, I used it before I
figured out how to use the float correctly with the CookieNumberPrinter to get the idle
game style.

## Inventory

### Buildings

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

## Builing Upgrades

Not implemented yet.

## Achievements

This was my first attempt at writing an Observer pattern style 
notification system. For the Cookie Amount & Cookies Per Second
Achievements, the wallet notifies the observer (the achievement list)
on a cookie increment.

The achievements themself are in `.csv files` in the `gamedata` folder
so you can add or remove achievements if you please.

## Wallet

Stores your cookies and the cps.

## Store

Lets you buy buildings. If you have enough cookies, you are able to buy things.
Things you buy land in your inventory. 

Price calculation is done for either 1 item, 10 items or 100 items, 
with an sort-of cheat calculation taken from the cookie clicker wiki. 
At first I calculated the exact price, but with gigantuous amounts of 
cookies the game crawled to a halt, so I optimized a bit with the formulas I found on the wiki. 

## Game loop

At first, the gameloop contained both the gameloop code and all text rendering 
and input handling code. When adding the `Views`, all rendering and input code 
was moved into their own views. 

The gameloop starts two threads, one for input handling and one
for the gamestep.

The game, before version 105, would sometimes crash when starting on a 
segfault. Never quite sure why, but in version 105 I moved the starting
of the two threads out of the gameloop constructor, and into a 
`start()` function, which `main.cpp` called after creating a 
`GameLoop`. Never saw that crash again.

### Game step

The game step thread displays all user input (renders text) and handles the
increment of cookies as per the current cookies per second value.

### User input

The user input thread handles all user input commands (like `c` to buy a cookie).

## User interface

Text based as you already guessed. Input it given in single key commands, seperate 
"tabs" (1/2/3/4/5 etc) for different interface parts.

## Savegame

The game is saved in your current folder, filename is `.cookieclicker.save`. 
Text based format, field seperated by a `;`. Don't manually edit the file or
you might loose your savegame. Currently savegame is prepared for newer things,
it has a version number in the savegame.

[1]: https://orteil.dashnet.org/cookieclicker/
[2]: screenshots/demo4.gif
[3]: screenshots/105_main.png
[4]: screenshots/105_achievements.png
[5]: screenshots/105_inventory.png
