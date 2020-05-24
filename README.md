# c_ookieclicker

![demo.gif][2]

c_ookieclicker is my personal pet project to experiment with c++. It is a clone of the famour
cookieclicker game [by ortiel][1]. A clone of a game is simple enough to get up and running fairly quickly, but also extensible enough when needed. How do you store huge score numbers when they don't fit in a `long long`? How do you write a game loop, how to use threads to handle user input? Saving a game (how to design a proper save format)? Also a great way to learn about project organization, software architecture and to try out design patterns.

# Different parts of the game

## CookieNumber

Class which allows storing of a large number (score, prices, inventory amount). Currently a typedef alias to Boosts multiprecision cpp_int.  
 

## Inventory

### Items

## Wallet

## Store

## Game loop

### Game step

### User input


## User interface

# Build

    git clone $this
    mkdir build
    cd build 
    cmake ..
    make
    
The game executable is:

    src/Game/src/Game.exe

[1]: https://orteil.dashnet.org/cookieclicker/
[2]: demo3.gif