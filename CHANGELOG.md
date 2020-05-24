# Version 101

Release date: 2020-05-224.

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
