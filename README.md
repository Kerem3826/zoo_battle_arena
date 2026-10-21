This is a simple C++ game where animals fight each other.
It uses classes and object-oriented programming.
To compile the game, open terminal and write: g++ oopProject.cpp -o oopGame Then run it with: ./oopGame
First the game asks how many teams you want Then you type names for each team and trainer Then you add animals to the teams
You choose the animal type and name Animal types are Vulture Bear Kangaroo Shark Duck After teams are ready you pick two teams to fight
In each turn you can attack or try to dodge or use trainer Attack has quick and special version Trainer can heal or buff
Some actions have cooldown Each animal has health, attack power, crit and evade chance Some can fly or run or swim These are used for evading
Evading uses chance and is not always successful The code uses Animal as base class Other animal types inherit from it Trainer and Team are also classes
BattleArena handles the fight You only call srand once in main Invalid input will ask you again Same team cannot fight itself File oopProject.h has all classes
File oopProject.cpp has the main function.