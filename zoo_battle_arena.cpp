#include "oopProject.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

int main() {

    srand(time(NULL)); // For randomness.

    vector<Team*> teams;
    vector<Trainer*> trainers;
    vector<Animal*> animals;

    int teamCount;

    cout << "How many teams do you want to be created? ";

    cin >> teamCount;

    for (int i = 0; i < teamCount; i++) {
        string teamName, trainerName;
        cout << "Enter name for Team " << i + 1 << ": ";
        cin >> teamName;
        cout << "Enter trainer name for " << teamName << ": ";
        cin >> trainerName;

        Team* team = new Team(teamName);
        Trainer* trainer = new Trainer(trainerName);
        team->selectTrainer(trainer);

        trainers.push_back(trainer);
        teams.push_back(team);

        int animalCount;
        cout << "How many animals for " << teamName << "? ";
        cin >> animalCount;

        for (int j = 0; j < animalCount; j++) {
            cout << "Choose animal " << j + 1 << " type:\n";
            cout << "  1) Vulture\n2) Bear\n3) Kangaroo\n4) Shark\n5) Duck\n";
            int choice;
            cin >> choice;

            cout << "Enter name for this animal: ";
            string animalName;
            cin >> animalName;

            Animal* a = nullptr;

            switch(choice){
                case 1: a = new Vulture(animalName, 100, 20); break;
                case 2: a = new Bear(animalName, 120, 18); break;
                case 3: a = new Kangaroo(animalName, 90, 22); break;
                case 4: a = new Shark(animalName, 110, 19); break;
                case 5: a = new Duck(animalName, 95, 17); break;
                default:
                    cout << "Invalid choice. Try again.\n";
                    break;
            }

            team->addAnimal(a);
            animals.push_back(a);
        }

        cout << teamName << " has been created successfully.\n\n";
    }

    cout << "\n--- Teams Ready ---\n";
    for (int i = 0; i < teams.size(); i++) {
        cout << i + 1 << ") " << teams[i]->getTeamName() << endl;
    }

    int t1, t2;
    cout << "Select first team to battle: ";
    cin >> t1;
    cout << "Select second team to battle: ";
    cin >> t2;

    if (t1 < 1 || t1 > teams.size()) {
    cout << "Invalid selection for first team.\n";
    return 0;
    }

    if (t2 < 1 || t2 > teams.size()) {
        cout << "Invalid selection for second team.\n";
        return 0;
    }

    if (t1 == t2) {
        cout << "You can't choose the same team twice.\n";
        return 0;
    }

    BattleArena arena;
    arena.selectTeams(teams[t1 - 1], teams[t2 - 1]); // Index shift
    arena.startBattle();

    return 0;
}