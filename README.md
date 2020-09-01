# c_ookieclicker

<a href="https://github.com/RaymiiOrg/c_ookieclicker/actions"><img src="https://github.com/RaymiiOrg/c_ookieclicker/workflows/C/C++%20CI/badge.svg" alt="ci badge"></a>

![demo.gif][2]

c_ookieclicker is my personal pet project to experiment with c++. It is a clone of the famous 
cookieclicker game [by ortiel][1]. A clone of a game is simple enough to get up and running 
fairly quickly, but also extensible enough when needed. How do you store huge score numbers 
when they don't fit in a `long long`? How do you write a game loop, how to use threads to handle 
user input? Saving a game (how to design a proper save format)? Also a great way to learn about 
project organization, software architecture and to try out design patterns.


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

# How to play

Start up the game. In the top you'll see your amount of cookies and
your Cookies per Second. Press `c`, then `Enter` to bake your first 
cookie. Repeat until you can buy items (like a cursor or grandma)
to automate your baking. There is no end to the game, but main goal
is to automate as much as possible. 
 
 
 

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

This was my first attempt at writing an Observer pattern style 
notification system. For the Cookie Amount Achievements, the 
wallet notifies the observer (the achievement list) on a cookie
increment.

The achievements themself are in `.csv files` in the `gamedata` folder
so you can add or remove achievements if you please.

## Wallet

Stores your cookies and the cps.

## Store

Lets you buy buildings. If you have enough cookies, you are able to buy things.
Things you buy land in your inventory. 

Price calculation is done for either 1 item, 10 items or 100 items, with an sort-of cheat
calculation taken from the cookie clicker wiki. At first I calculated the exact price, 
but with gigantuous amounts of cookies the game crawled to a halt, so I optimized a bit
with the formulas I found on the wiki. 

## Game loop

### Game step

### User input


## User interface

Text based as you already guessed. Input it given in single key commands, seperate 
"tabs" (1/2/3/4/5 etc) for different interface parts.

## Savegame

The game is saved in your current folder, filename is `.cookieclicker.save`. 
Text based format, field seperated by a `;`. Don't manually edit the file or
you might loose your savegame. Currently savegame is prepared for newer things,
it has a version number in the savegame.

[1]: https://orteil.dashnet.org/cookieclicker/
[2]: demo4.gif
