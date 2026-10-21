This is a simple C++ game where animals fight each other.
It uses classes and object-oriented programming.
To compile the game, open terminal and write: g++ zoo_battle_arena.cpp -o zooBattleArena Then run it with: ./zooBattleArena

First, the game asks how many teams you want, then you type names for each team and trainer. Then you add animals to the teams
You choose the animal type and name. Animal types are: Vulture, Bear, Kangaroo, Shark,and Duck. After teams are ready, you pick two teams to fight.
In each turn you can either attack, try to dodge, or use the Trainer. THE "attack" option has quick and special versions. Trainer can heal or buff your animal.
Some actions have cooldowns. Each animal has a health, an attack power, a crit chance and an evade chance. Some can fly, run or swim. These are features are used for evading.
Evading uses a chance variable and is not always successful. The code uses the "Animal" class as the base class and other animal types inherit from it. Trainer and Team are also classes.
BattleArena class handles the fight. You only call srand once in the "main()". Any invalid inputs will return you to the previous state until a valid input is given. A team cannot fight itself. File zoo_battle_arena.h contains all the classes.
File zoo_battle_arena.cpp has the main function.
