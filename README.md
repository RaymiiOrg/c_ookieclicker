# c_ookieclicker

<a href="https://github.com/RaymiiOrg/c_ookieclicker/actions"><img src="https://github.com/RaymiiOrg/c_ookieclicker/workflows/C/C++%20CI/badge.svg" alt="ci badge"></a>


![demo][6]

[More (1)][3] [screenshots (2)][4] [here (3)][5].

c_ookieclicker is my personal pet project to experiment with c++. It is a clone of the famous 
cookieclicker game [by ortiel][1]. A clone of a game is simple enough to get up and running 
fairly quickly, but also extensible enough when needed. How do you itemstore huge score numbers 
when they don't fit in a `long long`? How do you write a game loop, how to use threads to handle 
user input? Saving a game (how to design a proper save format)? Also a great way to learn about 
project organization, software architecture and to try out design patterns.


# How to play

Release binaries can be found in the `releases` folder. The latest release will
always be the current development version, which is unstable at best.  

Debian packages can be found [here including the build scripts](https://github.com/RaymiiOrg/c_ookieclicker_debian_package)

Either download a package, release binary or clone the git repo and build yourself.

Start up the game. In the top you'll see your amount of cookies and
your Cookies per Second. Press `c`, then `Enter` to bake your first 
cookie. Repeat until you can buy items (like a cursor or grandma)
to automate your baking. There is no end to the game, but main goal
is to automate as much as possible. 


# License

Copyright 2021 - Remy van Elst.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

# Build

How to build the game for yourself. Boost is a required dependency, but it is possible
to build without it. When you reach the limit of what fits in an `long double`, 
the score (and other numbers, such as item amount or cost, will overflow).

Install `boost` and build dependencies. On Ubuntu 18.04:

    sudo apt install libboost-dev-all build-essential cmake
 
Clone the repository:

    git clone https://github.com/RaymiiOrg/c_ookieclicker/
    
Build locally: 

    mkdir build
    cmake -Bbuild -H.
    cmake --build build/ --target all -DCMAKE_BUILD_TYPE=Release -DUSEBOOST_MPP=Y
    # or old fashioned:
    # cd build
    # cmake .. -DCMAKE_BUILD_TYPE=Release -DUSEBOOST_MPP=Y
    # make
    
The game executable is:

    src/Game/src/c_ookieclicker_linux
    
Make sure to run it in the cloned folder, otherwise some game data might not load, like
then achievements. Game data files are in:
    
    releases/$version/gamedata
    
and are symlinked in the main folder you cloned from github.

## Cmake compile flags

- `STATIC_COMPILE` - if set to `Y`, compiles a static binary. Works only on linux and is used to cross-compile to arm.
- `BUILD_TESTS` - if set to `Y`, compiles the unit tests (googletest)
- `USEBOOST_MPP` - if set to `Y`, compiles with boost multiprecision. Otherwise, a `long double` is used as the number storage.

You can pass cmake options with the `-D` flag. An example to build the tests, with boost multiprecision support:

    cmake .. -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTS=Y -DUSEBOOST_MPP=Y

See the `cmakeConfig.h.in` file and the `src/CmakeLists.txt` file to see how these options passed along
to the C++ code.

# Different parts of the game

## CookieNumber

Class which allows storing of a large number (score, prices, inventory amount). 
Currently a typedef alias to Boosts multiprecision `cpp_dec_float`. Or, if compiled
without the CMAKE flag `-DUSEBOOST_MPP=Y`, a simple and primitive template type that supports
printing methods and some basic operators. Allowing compilation without boost should 
speed up the build and allow for usage on platforms / compilers without boost.
In practical terms it means that when you overflow a `long double`, the game is unable
to count numbers (scores, prices, etc) and will show `inf` (for infinity). 
 
Supports printing in format used by other incremental games. 
  - Example: `1000000000000000000000` becomes `1 sextillion`. 
  - Example: `21341831944003682716936974836612280224172215802627435299099076055022090949593824685640853139456777002501904985670414671748540291630152113086259344562839841917575524836560787544358350755299402239335813148535474932165751` becomes `21xx`.

Look at the `CookieNumberPrinter` class how I print in the incremental / idle game style. 

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

## ItemStore

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


# long double limit

If you want to experiment with overflowing the score, compile a non-boost version
and edit your savefile to have more than the below number of cookies: 

    1189731495357231765021263853030970205169063322294624200440323733891737005522970722616410290336528882853545697807495577314427443153670288434198125573853743678673593200706973263201915918282961524365529510646791086614311790632169778838896134786560600399148753433211454911160088679845154866512852340149773037600009125479393966223151383622417838542743917838138717805889487540575168226347659235576974805113725649020884855222494791399377585026011773549180099796226026859508558883608159846900235645132346594476384939859276456284579661772930407806609229102715046085388087959327781622986827547830768080040150694942303411728957777100335714010559775242124057347007386251660110828379119623008469277200965153500208474470792443848545912886723000619085126472111951361467527633519562927597957250278002980795904193139603021470997035276467445530922022679656280991498232083329641241038509239184734786121921697210543484287048353408113042573002216421348917347174234800714880751002064390517234247656004721768096486107994943415703476320643558624207443504424380566136017608837478165389027809576975977286860071487028287955567141404632615832623602762896316173978484254486860609948270867968048078702511858930838546584223040908805996294594586201903766048446790926002225410530775901065760671347200125846406957030257138960983757998926954553052368560758683179223113639519468850880771872104705203957587480013143131444254943919940175753169339392366881856189129931729104252921236835159922322050998001677102784035360140829296398115122877768135706045789343535451696539561254048846447169786893211671087229088082778350518228857646062218739702851655083720992349483334435228984751232753726636066213902281264706234075352071724058665079518217303463782631353393706774901950197841690441824738063162828586857741432581165364040218402724913393320949219498422442730427019873044536620350262386957804682003601447291997123095530057206141866974852846856186514832715974481203121946751686379343096189615107330065552421485195201762858595091051839472502863871632494167613804996319791441870254302706758495192008837915169401581740046711477877201459644461175204059453504764721807975761111720846273639279600339670470037613374509553184150073796412605047923251661354841291884211340823015473304754067072818763503617332908005951896325207071673904547777129682265206225651439919376804400292380903112437912614776255964694221981375146967079446870358004392507659451618379811859392049544036114915310782251072691486979809240946772142727012404377187409216756613634938900451232351668146089322400697993176017805338191849981933008410985993938760292601390911414526003720284872132411955424282101831204216104467404621635336900583664606591156298764745525068145003932941404131495400677602951005962253022823003631473824681059648442441324864573137437595096416168048024129351876204668135636877532814675538798871771836512893947195335061885003267607354388673368002074387849657014576090349857571243045102038730494854256702479339322809110526041538528994849203991091946129912491633289917998094380337879522093131466946149705939664152375949285890960489916121944989986384837022486672249148924678410206183364627416969576307632480235587975245253737035433882960862753427740016333434055083537048507374544819754722228975281083020898682633020285259923084168054539687911418297629988964576482765287504562854924265165217750799516259669229114977788962356670956627138482018191348321687995863652637620978285070099337294396784639879024914514222742527006363942327998483976739987154418554201562244154926653014515504685489258620276085761837129763358761215382565129633538141663949516556000264159186554850057052611431952919918807954522394649627635630178580896692226406235382898535867595990647008385687123810329591926494846250768992258419305480763620215089022149220528069842018350840586938493815498909445461977893029113576516775406232278298314033473276603952231603422824717528181818844304880921321933550869873395861276073670866652375555675803171490108477320096424318780070008797346032906278943553743564448851907191616455141155761939399690767415156402826543664026760095087523945507341556135867933066031744720924446513532366647649735400851967040771103640538150073486891798364049570606189535005089840913826869535090066783324472578712196604415284924840041850932811908963634175739897166596000759487800619164094854338758520657116541072260996288150123144377944008749301944744330784388995701842710004808305012177123560622895076269042856800047718893158089358515593863176652948089031267747029662545110861548958395087796755464137944895960527975209874813839762578592105756284401759349324162148339565350189196811389091843795734703269406342890087805846940352453479398080674273236297887100867175802531561302356064878709259865288416350972529537091114317204887747405539054009425375424119317944175137064689643861517718849867010341532542385911089624710885385808688837777258648564145934262121086647588489260031762345960769508849149662444156604419552086811989770240

This is on my system the output of `std::numeric_limits<long double>::max()`. 
Nothing exciting happens, the score just changes to `inf`.

With boost multprecision, when the list of suffixes runs out, you get a 
scientific notation representation of your amount of cookies. Boring, 
but it works:
    
    Cookies :       124.046e+6532
    cps     :       722.016e+6534 



[1]: https://orteil.dashnet.org/cookieclicker/
[2]: screenshots/demo4.gif
[3]: screenshots/105_main.png
[4]: screenshots/105_achievements.png
[5]: screenshots/105_inventory.png
[6]: screenshots/demo_105.gif