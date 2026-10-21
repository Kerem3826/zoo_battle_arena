#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

bool chance(int limit){ // Checks if the chances hit.

    if(((rand() % 100 ) + 1) <= limit){

        return true;

    }

    else {
        return false;
    }
}

class Animal{

    protected:

        string species;
        string name;
        int maxHealth;
        int health;
        int attackPower;
        string quickAttack;
        string specialAttack;
        int critChance;
        int evadeChance;
        int specialAttackCD = 0;
        bool isBuffed = false;

    public:

        Animal(string species, string name, int maxHealth, int attackPower, string quickAttack, string specialAttack, int critChance, int evadeChance){
            this->species = species;
            this->name = name;
            this->maxHealth = maxHealth;
            this->health = maxHealth;
            this->attackPower = attackPower;
            this->quickAttack = quickAttack;
            this->specialAttack = specialAttack;
            this->critChance = critChance;
            this->evadeChance = evadeChance;

        }

        virtual void performAttack(Animal* opponent) = 0;
        virtual void takeDamage(int damage);
        virtual void showPassive() = 0;
        virtual void evade() = 0;

        virtual void introduce(){

            cout << "Animal Info:\n" << endl;
            cout << "   Name: " << name << endl;
            cout << "   Species: " << species << endl;
            cout << "   Health: " << health << endl;
            cout << "   Attack Power: " << attackPower << endl << endl;
            
            cout << "   Attacks: " << endl;
            cout << "       1-) Quick Attack | " << quickAttack << ": Deals " << attackPower << " damage. (Base)" << endl;
            cout << "       2-) Special Attack | " << specialAttack << ": Deals " << (attackPower*3) << " damage. Cooldown: " << specialAttackCD << " rounds. (Base)" << endl;

        }

        string getSpecies(){
            return species;
        }

        void setName(string newName){
            this->name = newName;
        }

        string getName(){
            return name;
        }

        void setMaxHealth(int newMaxHealth){
            this->maxHealth = newMaxHealth;
        }

        int getMaxHealth(){
            return maxHealth;
        }

        void setHealth(int newHealth){
            this->health = newHealth;
        }

        int getHealth(){
            return health;
        }

        void setAttackPower(int newAP){
            this->attackPower = newAP;
        }

        int getAttackPower(){
            return attackPower;
        }

        void setQuickAttack(string newQA){
            this->quickAttack = newQA;
        }

        string getQuickAttack(){
            return quickAttack;
        }

        void setSpecialAttack(string newSA){
            this->specialAttack = newSA;
        }

        string getSpecialAttack(){
            return specialAttack;
        }
        
        void setCritChance(int newCC){
            this->critChance = newCC;
        }
        
        int getCritChance(){
            return critChance;
        }

        void setEvadeChance(int newEC){
            this->evadeChance = newEC;
        }
        
        int getEvadeChance(){
            return evadeChance;
        }

        void setSpecialAttackCD(int cd){
            this->specialAttackCD = cd;
        }

        int getSpecialAttackCD(){
            return specialAttackCD;
        }

        void setBuff(bool tf){
            this->isBuffed = tf;
        }
};

//////////////////////////////////////////////////////////////////////////////////////////////////

class Flyable{

    private:

        bool isFlying = false;

    public:

        virtual bool fly() = 0;
        virtual bool getFlight(){
            return isFlying;
        }
        virtual void setFlight(bool tf){
            this->isFlying = tf;
        }

};

class Runnable{

    private:

        bool isRunning = false;

    public:

        virtual bool run() = 0;
        virtual bool getRun(){
            return isRunning;
        }
        virtual void setRun(bool tf){
            this->isRunning = tf;
        }

};

class Swimmable{

    private:

        bool isSwimming = false;

    public:

        virtual bool swim() = 0;
        virtual bool getSwim(){
            return isSwimming;
        }
        virtual void setSwim(bool tf){
            this->isSwimming = tf;
        }


};

//////////////////////////////////////////////////////////////////////////////////////////////////

class Vulture : public Animal, public Flyable{

    public:

        Vulture(string name, int health, int attackPower) : Animal("Vulture", name, health, attackPower, "Claw Swipe", "Death Dive", 20, 40){
        }

        void performAttack(Animal* opponent) override;
        void takeDamage(int damage) override;
        void showPassive() override;
        void introduce() override;
        void evade() override;
        bool fly() override;
        
        

};

void Vulture::performAttack(Animal* opponent){

    int choice;

    if(isBuffed){
        setAttackPower(getAttackPower() + 5);
    }

    int damage = getAttackPower() + ( ( ( (opponent->getMaxHealth()) - (opponent->getHealth()) ) / opponent->getMaxHealth() ) * getAttackPower() ); // Because of Vultures' passive.

    if(chance(this->getCritChance())){ // If the crit chance hits, the damage is multiplied by (1.5).
        damage *=1.5;
    }

    cout << "Choose your attack!\n" << endl;
    cout << "   1-) Quick Attack | " << getQuickAttack() << ": Deals " << damage << " damage." << endl;
    cout << "   2-) Special Attack | " << getSpecialAttack() << ": Deals " << (damage*2) << " damage." << endl;

    while(1){

        cin >> choice;

        if( choice == 1 ){
            cout << getName() << "(" << getSpecies() << ") used " << getQuickAttack() << "! 🌪" << endl;
            opponent->takeDamage(damage);
            break;
        }
        else if(getSpecialAttackCD() != 0){
            cout << "Special Attack is on cooldown. Remaining rounds: " << getSpecialAttackCD() << endl;
            continue;
        }
        else if( getSpecialAttackCD() == 0){
            if( choice == 2 ){
                cout << getName() << "(" << getSpecies() << ") used " << getSpecialAttack() << "! 🌀" << endl;
                opponent->takeDamage(damage*2);
                setSpecialAttackCD(2);
                break;
            }
        }
        else{
            cout << "Invalid choice, please try again." << endl;
            continue;
        } 
    }

    if(isBuffed){
        setAttackPower(getAttackPower() - 5);
        setBuff(false);
    }

}

void Vulture::takeDamage(int damage){

    if(this->getFlight() == true){
        if( this->fly() == true ){
            this->setFlight(false);
            return;
        }
    }
    else{
        this->setHealth(this->getHealth() - damage);
        cout << getName() << " took " << damage << " damage! 💥" << endl;
    }
}

void Vulture::showPassive(){
    cout << "Vultures deal more damage proportional to the opponent's missing health." << endl;
}

void Vulture::introduce(){

    cout << "Animal Info:\n" << endl;
    cout << "   Name: " << getName() << endl;
    cout << "   Species: " << getSpecies() << endl;
    cout << "   Max Health: " << getMaxHealth() << endl;
    cout << "   Current Health: " << getHealth() << endl;
    cout << "   Attack Power: " << getAttackPower() << endl << endl;
        
    cout << "   Attacks: " << endl;
    cout << "       1-) Quick Attack | " << getQuickAttack() << ": Deals up to " << getAttackPower() *2 << " damage according to opponent's missing health. (Base damage: " << getAttackPower() << ")" << endl;
    cout << "       2-) Special Attack | " << getSpecialAttack() << ": Deals up to " << getAttackPower() *4 << " damage according to opponent's missing health. (Base damage: " << getAttackPower()*2 << ")" << endl;

}

void Vulture::evade(){
    fly();
}

bool Vulture::fly(){

    if(chance(this->getEvadeChance())){
        cout << this->getName() << " flied and escaped the attack! 🦅💨" << endl;
        this->setFlight(true);
        return true;
    }
    else{
        cout << this->getName() << " tried to fly but failed! ❌" << endl;
        return false;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////

class Bear : public Animal, public Runnable{

    public:

        Bear(string name, int health, int attackPower) : Animal("Bear", name, health, attackPower, "Grizzly Jab", "Mortal Maul", 25, 35){
        }

        void performAttack(Animal* opponent) override;
        void takeDamage(int damage) override;
        void showPassive() override;
        void introduce() override;
        void evade() override;
        bool run() override;
        

};

void Bear::performAttack(Animal* opponent){
    int choice;

    if(isBuffed){
            setAttackPower(getAttackPower() + 5);
    }

    int damage = getAttackPower();

    if(chance(this->getCritChance())){ // If the crit chance hits, the damage is multiplied by (1.5).
        damage *=1.5;
    }

    cout << "Choose your attack!\n" << endl;
    cout << "   1-) Quick Attack | " << getQuickAttack() << ": Deals " << damage << " damage." << endl;
    cout << "   2-) Special Attack | " << getSpecialAttack() << ": Deals " << (damage*3) << " damage." << endl;
    
    while(1){

        cin >> choice;

        if( choice == 1 ){
            cout << getName() << "(" << getSpecies() << ") used " << getQuickAttack() << "! 🥊" << endl;
            opponent->takeDamage(damage);
            break;
        }
        else if(getSpecialAttackCD() != 0){
            cout << "Special Attack is on cooldown. Remaining rounds: " << getSpecialAttackCD() << endl;
            continue;
        }
        else if(getSpecialAttackCD() == 0){
            if( choice == 2 ){
                cout << getName() << "(" << getSpecies() << ") used " << getSpecialAttack() << "! 💀" << endl;
                opponent->takeDamage(damage*3);
                setSpecialAttackCD(2);
                break;
            }
        }
        else{
            cout << "Invalid choice, please try again." << endl;
            continue;
        } 
    }

    if(isBuffed){
        setAttackPower(getAttackPower() - 5);
        setBuff(false);
    }

}

void Bear::takeDamage(int damage){

    if(this->getRun() == true){
        if( this->run() == true ){
            this->setRun(false);
            return;
        }
    }
    else{

        damage = ( damage*0.3 + (damage*0.7 * (1.1 * ( this->getHealth() / this->getMaxHealth() ) ) ) ); // Because of Bear's passive, Bear gets 30% of the damage directly and 70% of the damage reduced proportional to the missing health of itself.

        this->setHealth( this->getHealth() - damage );

        cout << getName() << " took " << damage << " damage! 💥" << endl;

    }
}

void Bear::showPassive(){
    cout << "Bears take less damage proportional to their missing health." << endl;
}

void Bear::introduce(){

    cout << "Animal Info:\n" << endl;
    cout << "   Name: " << getName() << endl;
    cout << "   Species: " << getSpecies() << endl;
    cout << "   Max Health: " << getMaxHealth() << endl;
    cout << "   Current Health: " << getHealth() << endl;
    cout << "   Attack Power: " << getAttackPower() << endl << endl;
        
    cout << "   Attacks: " << endl;
    cout << "       1-) Quick Attack | " << getQuickAttack() << ": Deals " << getAttackPower() << " damage. " << endl;
    cout << "       2-) Special Attack | " << getSpecialAttack() << ": Deals " << getAttackPower() *3 << " damage. " << endl;

}

void Bear::evade(){
    run();
}

bool Bear::run(){

    if(chance(this->getEvadeChance())){
        cout << this->getName() << " ran and escaped the attack! 🐻💨" << endl;
        this->setRun(true);
        return true;
    }
    else{
        cout << this->getName() << " tried to run but failed! ❌" << endl;
        return false;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////

class Kangaroo : public Animal, public Runnable{

    public:

        Kangaroo(string name, int health, int attackPower) : Animal("Kangaroo", name, health, attackPower, "Quick Sweep", "Thunder Kick", 30, 30){
        }

        void performAttack(Animal* opponent) override;
        void takeDamage(int damage) override;
        void showPassive() override;
        void introduce() override;
        void evade() override;
        bool run() override;
        

};

void Kangaroo::performAttack(Animal* opponent){
    int choice;

    if(isBuffed){
        setAttackPower(getAttackPower() + 5);
    }

    int damage = getAttackPower();

    if(chance(this->getCritChance())){ // If the crit chance hits, the damage is multiplied by (1.5).
        damage *=1.5;
    }

    cout << "Choose your attack!\n" << endl;
    cout << "   1-) Quick Attack | " << getQuickAttack() << ": Deals " << damage << " damage." << endl;
    cout << "   2-) Special Attack | " << getSpecialAttack() << ": Deals " << (damage*3) << " damage." << endl;

    while(1){

        cin >> choice;

        if( choice == 1 ){
            cout << getName() << "(" << getSpecies() << ") used " << getQuickAttack() << "! 🦵" << endl;
            opponent->takeDamage(damage + ( chance(getCritChance()) ? damage*0.3 : 0 ) ); // Because of Kangaroo's passive, there is a (crit percent) chance of baby kangaroo also dealing 30% of the damage dealt.
            break;
        }
        else if(getSpecialAttackCD() != 0){
            cout << "Special Attack is on cooldown. Remaining rounds: " << getSpecialAttackCD() << endl;
            continue;
        }
        else if(getSpecialAttackCD() == 0){
            if( choice == 2 ){
                cout << getName() << "(" << getSpecies() << ") used " << getSpecialAttack() << "! ⚡" << endl;
                opponent->takeDamage( (damage + ( chance(getCritChance()) ? damage*0.3 : 0 ) ) *3);
                setSpecialAttackCD(2);
                break;
            }
        }
        else{
            cout << "Invalid choice, please try again." << endl;
            continue;
        } 
    }

    if(isBuffed){
        setAttackPower(getAttackPower() - 5);
        setBuff(false);
    }

}

void Kangaroo::takeDamage(int damage){

    if(this->getRun() == true){
        if( this->run() == true ){
            this->setRun(false);
            return;
        }
    }
    else{
        this->setHealth(this->getHealth() - damage);
        cout << getName() << " took " << damage << " damage! 💥" << endl;
    }
}

void Kangaroo::showPassive(){
    cout << "Kangaroos have a chance (which is equal to their crit chance) of the baby kangaroo inside their pockets also dealing the 30%% of the damage they dealt." << endl;
}

void Kangaroo::introduce(){

    cout << "Animal Info:\n" << endl;
    cout << "   Name: " << getName() << endl;
    cout << "   Species: " << getSpecies() << endl;
    cout << "   Max Health: " << getMaxHealth() << endl;
    cout << "   Current Health: " << getHealth() << endl;
    cout << "   Attack Power: " << getAttackPower() << endl << endl;
        
    cout << "   Attacks: " << endl;
    cout << "       1-) Quick Attack | " << getQuickAttack() << ": Deals up to " << getAttackPower() *1.3 << " damage via the baby kangaroo. (Base damage: " << getAttackPower() << ")" << endl;
    cout << "       2-) Special Attack | " << getSpecialAttack() << ": Deals up to " << getAttackPower() *3.9 << " damage via the baby kangaroo. (Base damage: " << getAttackPower()*3 << ")" << endl;

}

void Kangaroo::evade(){
    run();
}

bool Kangaroo::run(){

    if(chance(this->getEvadeChance())){
        cout << this->getName() << " ran and escaped the attack! 🦘💨" << endl;
        this->setRun(true);
        return true;
    }
    else{
        cout << this->getName() << " tried to run but failed! ❌" << endl;
        return false;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////

class Shark : public Animal, public Swimmable{

    public:

        Shark(string name, int health, int attackPower) : Animal("Shark", name, health, attackPower, "Tail Whip", "Bloody Bite", 15, 45){
        }

        void performAttack(Animal* opponent) override;
        void takeDamage(int damage) override;
        void showPassive() override;
        void introduce() override;
        void evade() override;
        bool swim() override;
        

};

void Shark::performAttack(Animal* opponent){
    int choice;

    if(isBuffed){
        setAttackPower(getAttackPower() + 5);
    }

    int damage = getAttackPower();

    if(chance(this->getCritChance())){ // If the crit chance hits, the damage is multiplied by (1.5).
        damage *=1.5;
    }

    cout << "Choose your attack!\n" << endl;
    cout << "   1-) Quick Attack | " << getQuickAttack() << ": Deals " << damage << " damage." << endl;
    cout << "   2-) Special Attack | " << getSpecialAttack() << ": Deals " << (damage*3) << " damage." << endl;
    
    while(1){

        cin >> choice;

        if( choice == 1 ){
            cout << getName() << "(" << getSpecies() << ") used " << getQuickAttack() << "! 🌊" << endl;
            opponent->takeDamage(damage);
            break;
        }
        else if(getSpecialAttackCD() != 0){
            cout << "Special Attack is on cooldown. Remaining rounds: " << getSpecialAttackCD() << endl;
            continue;
        }
        else if(getSpecialAttackCD() == 0){
            if( choice == 2 ){
                cout << getName() << "(" << getSpecies() << ") used " << getSpecialAttack() << "! 🩸" << endl;
                opponent->takeDamage(damage*3);
                setSpecialAttackCD(2);
                break;
            }
        }
        else{
            cout << "Invalid choice, please try again." << endl;
            continue;
        } 
    }

    if(isBuffed){
        setAttackPower(getAttackPower() - 5);
        setBuff(false);
    }

}

void Shark::takeDamage(int damage){

    if(this->getSwim() == true){
        if( this->swim() == true ){
            this->setSwim(false);
            return;
        }

        this->setHealth(this->getHealth() - damage*0.95); // Because of Shark's passive, whenever it fails to evade, the damage it takes reduces by 5% for the current round.
        cout << "Damage taken by " << getName() << " has been reduced by 5% this round!" << endl;
        cout << getName() << " took " << damage*0.95 << " damage! 💥" << endl;

        return;
    }
    else{

        this->setHealth(this->getHealth() - damage);

        cout << getName() << " took " << damage << " damage! 💥" << endl;
    }
}

void Shark::showPassive(){
    cout << "Sharks gain +5%% evade chance whenever they successfully evade and take 5%% less damage if they try but fail to evade." << endl;
}

void Shark::introduce(){

    cout << "Animal Info:\n" << endl;
    cout << "   Name: " << getName() << endl;
    cout << "   Species: " << getSpecies() << endl;
    cout << "   Max Health: " << getMaxHealth() << endl;
    cout << "   Current Health: " << getHealth() << endl;
    cout << "   Attack Power: " << getAttackPower() << endl << endl;
        
    cout << "   Attacks: " << endl;
    cout << "       1-) Quick Attack | " << getQuickAttack() << ": Deals " << getAttackPower() << " damage. " << endl;
    cout << "       2-) Special Attack | " << getSpecialAttack() << ": Deals " << getAttackPower() *3 << " damage. " << endl;

}

void Shark::evade(){
    swim();
}

bool Shark::swim(){

    if(chance(this->getEvadeChance())){

        cout << this->getName() << " swam and escaped the attack! 🦈💨" << endl;
        this->setSwim(true);

        if(getEvadeChance() <= 95 ){
            this->setEvadeChance(getEvadeChance() + 5); // Because of Shark's passive, it gains +5% evade chance whenever it successfully evades.
            cout << "Evade chance increased by +5%!" << endl;
        }
        else{
            cout << "Evade chance cannot go over 100%." << endl;
        }

        return true;
    }
    else{
        cout << this->getName() << " tried to swim but failed! ❌" << endl;
        return false;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////

class Duck : public Animal, public Flyable, public Runnable, public Swimmable{

    public:

        Duck(string name, int health, int attackPower) : Animal("Duck", name, health, attackPower, "Swift Peck", "Wing Smash", 35, 30){
        }

        void performAttack(Animal* opponent) override;
        void takeDamage(int damage) override;
        void showPassive() override;
        void introduce() override;
        void evade() override;
        bool fly() override;
        bool run() override;
        bool swim() override;
        

};

void Duck::performAttack(Animal* opponent){
    int choice;

    if(isBuffed){
        setAttackPower(getAttackPower() + 5);
    }

    int damage = getAttackPower();

    if(chance(this->getCritChance())){ // If the crit chance hits, the damage is multiplied by (1.5).
        damage *=1.5;
    }

    cout << "Choose your attack!\n" << endl;
    cout << "   1-) Quick Attack | " << getQuickAttack() << ": Deals " << damage << " damage." << endl;
    cout << "   2-) Special Attack | " << getSpecialAttack() << ": Deals " << (damage*3) << " damage." << endl;
    
    while(1){

        cin >> choice;

        if( choice == 1 ){
            cout << getName() << "(" << getSpecies() << ") used " << getQuickAttack() << "! 🥊" << endl;
            opponent->takeDamage(damage);
            break;
        }
        else if(getSpecialAttackCD() != 0){
            cout << "Special Attack is on cooldown. Remaining rounds: " << getSpecialAttackCD() << endl;
            continue;
        }
        else if(getSpecialAttackCD() == 0){
            if( choice == 2 ){
                cout << getName() << "(" << getSpecies() << ") used " << getSpecialAttack() << "! 💀" << endl;
                opponent->takeDamage(damage*3);
                setSpecialAttackCD(2);
                break;
            }
        }
        else{
            cout << "Invalid choice, please try again." << endl;
            continue;
        } 
    }

    if(isBuffed){
        setAttackPower(getAttackPower() - 5);
        setBuff(false);
    }

}

void Duck::takeDamage(int damage){

    if(this->getFlight() == true){ // Because of Duck's passive, it can either Fly, Run or Swim so whenever it tries to evade, it tries each 3 of them at the same time.
        if( this->fly() == true ){
            this->setFlight(false);
            return;
        }
    }

    else if(this->getRun() == true){
        if( this->run() == true ){
            this->setRun(false);
            return;
        }
    }

    else if(this->getSwim() == true){
        if( this->swim() == true ){
            this->setSwim(false);
            return;
        }
    }

    else{

        this->setHealth( this->getHealth() - damage );

        cout << getName() << " took " << damage << " damage! 💥" << endl;

    }
}

void Duck::showPassive(){
    cout << "Since Ducks can Fly, Run and Swim, whenever they try to evade an attack, all 3 of the evasion actions are tried." << endl;
}

void Duck::introduce(){

    cout << "Animal Info:\n" << endl;
    cout << "   Name: " << getName() << endl;
    cout << "   Species: " << getSpecies() << endl;
    cout << "   Max Health: " << getMaxHealth() << endl;
    cout << "   Current Health: " << getHealth() << endl;
    cout << "   Attack Power: " << getAttackPower() << endl << endl;
        
    cout << "   Attacks: " << endl;
    cout << "       1-) Quick Attack | " << getQuickAttack() << ": Deals " << getAttackPower() << " damage. " << endl;
    cout << "       2-) Special Attack | " << getSpecialAttack() << ": Deals " << getAttackPower() *3 << " damage. " << endl;

}

void Duck::evade(){
    fly();
    run();
    swim();
}

bool Duck::fly(){

    if(chance(this->getEvadeChance())){
        cout << this->getName() << " flied and escaped the attack! 🦆💨" << endl;
        this->setFlight(true);
        return true;
    }
    else{
        cout << this->getName() << " tried to fly but failed! ❌" << endl;
        return false;
    }
}

bool Duck::run(){

    if(chance(this->getEvadeChance())){
        cout << this->getName() << " ran and escaped the attack! 🦆💨" << endl;
        this->setRun(true);
        return true;
    }
    else{
        cout << this->getName() << " tried to run but failed! ❌" << endl;
        return false;
    }
}

bool Duck::swim(){

    if(chance(this->getEvadeChance())){
        cout << this->getName() << " swam and escaped the attack! 🦆💨" << endl;
        this->setSwim(true);
        return true;
    }
    else{
        cout << this->getName() << " tried to swim but failed! ❌" << endl;
        return false;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////

class Trainer{

    private:

        string name;
        int healCD = 0;
        int buffCD = 0;

    public:

        Trainer(string name){
            this->name = name;
        }

        void setName(string newName){
            this->name = newName;
        }

        string getName(){
            return name;
        }

        void setHealCD(int cd){
            this->healCD = cd;
        }

        int getHealCD(){
            return healCD;
        }

        void setBuffCD(int cd){
            this->buffCD = cd;
        }

        int getBuffCD(){
            return buffCD;
        }

        void healAnimal(Animal* animal){
            if(getHealCD() == 0){

                if(animal->getHealth() >= animal->getMaxHealth() * 0.8){
                    animal->setHealth(animal->getMaxHealth());
                }
                else{
                    animal->setHealth(animal->getHealth() + animal->getMaxHealth()*0.2);
                }

                setHealCD(2);

            }

            else{
                cout << "Heal is on cooldown. Remaining rounds: " << getHealCD() << endl;
            }
        }

        void buffAnimal(Animal* animal){
            if(getBuffCD() == 0){
                animal->setBuff(true);
                setBuffCD(2);
            }
            else{
                cout << "Buff is on cooldown. Remaining rounds: " << getBuffCD() << endl;
            }
        }


};

//////////////////////////////////////////////////////////////////////////////////////////////////

class Team{

    private:

        string teamName;
        vector<Animal*> animals;
        Trainer* trainer = nullptr;

    public:

        Team(string teamName){
            this->teamName = teamName;
        }

        void addAnimal(Animal* animal){
            animals.push_back(animal);
        }

        Animal* getAnimal(int index){
            return animals[index];
        }

        Trainer* getTrainer(){
            return trainer;
        }

        void selectTrainer(Trainer* trainer){
            this->trainer = trainer;
        }

        void displayTeam(){

            cout << "Team Name: " << getTeamName() << endl;

            if(trainer!=nullptr){
                cout << "Trainer: " << trainer->getName() << endl;
            }

            for(int i=0 ; i<animals.size(); i++){
                cout << i+1 << "-) " << animals[i]->getName() << " (" << animals[i]->getSpecies() << ")" << endl;
            }
        }
        void displayAnimals(){
            for(int i=0 ; i<animals.size(); i++){
                cout << i+1 << "-) " << animals[i]->getName() << " (" << animals[i]->getSpecies() << ")" << endl;
            }
        }

        void displayAnimal(Animal* animal){
            animal->introduce();
        }

        void setTeamName(string newTN){
            this->teamName = newTN;
        }
        
        string getTeamName(){
            return teamName;
        }

        int getTeamSize(){
            return animals.size();
        }

};

//////////////////////////////////////////////////////////////////////////////////////////////////

class BattleArena{

    private:

        Team* team1;
        Team* team2;

    public:

        void selectTeams(Team* team1, Team* team2){
            this->team1 = team1;
            this->team2 = team2;
        }

        void startBattle(){

            while(true){

                int choice;
                int animalIndex1;
                int animalIndex2;

                cout << "Battle has started! Team " << team1->getTeamName() << " starts!\n" << endl;

                cout << "Team 1, " << team1->getTeamName() << " Choose an animal to battle with:" << endl;

                    team1->displayAnimals();

                    cin >> animalIndex1;

                    if(animalIndex1 < 1 || animalIndex1 > team1->getTeamSize()){
                        cout << "Invalid choice. Please try again." << endl;
                        continue;
                    }
                    else{
                        animalIndex1-=1; // Because index starts with 0.
                    }

                cout << "Team 2, " << team2->getTeamName() << " Choose an animal to battle with:" << endl;

                    team2->displayAnimals();

                    cin >> animalIndex2;

                    if(animalIndex2 < 1 || animalIndex2 > team2->getTeamSize()){
                        cout << "Invalid choice. Please try again." << endl;
                        continue;
                    }
                    else{
                        animalIndex2-=1; // Because index starts with 0.
                    }


                while (true){

                    cout << "Team " << team1->getTeamName() << "'s turn!" << endl; // Team 1's Turn


                    while(true){
                        cout << "Choose action:" << endl;
                        cout << "   1-) Animal" << endl;
                        cout << "   2-) Trainer" << endl;

                        cin >> choice;

                        if(choice == 1){

                            while(true){

                                cout << "Choose action:" << endl;
                                cout << "   1-) Attack" << endl;
                                cout << "   2-) Evade" << endl;

                                cin >> choice;

                                if(choice == 1){

                                    team1->getAnimal(animalIndex1)->performAttack(team2->getAnimal(animalIndex2));

                                    if(team2->getAnimal(animalIndex2)->getHealth() <= 0){
                                        cout << "Battle has ended! The winner is: " << team1->getTeamName() << endl; // Battle ends if opponent's health drops to 0.
                                        return;
                                    }
                                }

                                else if(choice == 2){
                                    Animal* a = team1->getAnimal(animalIndex1);

                                    if (Flyable* f = dynamic_cast<Flyable*>(a)) {
                                        f->fly();
                                    }

                                    if (Runnable* r = dynamic_cast<Runnable*>(a)) {
                                        r->run();
                                    }

                                    if (Swimmable* s = dynamic_cast<Swimmable*>(a)) {
                                        s->swim();
                                    }
                                }

                                else{
                                    cout << "Invalid choice, please try again." << endl;
                                    continue;
                                }


                                break;
                            }

                            break;
                        }

                        else if(choice == 2){

                            cout << "Choose action:" << endl;
                                cout << "   1-) Heal" << endl;
                                cout << "   2-) Buff" << endl;

                                cin >> choice;

                                if(choice == 1){

                                    team1->getTrainer()->healAnimal(team1->getAnimal(animalIndex1));
                                    break;
                                }

                                else if(choice == 2){

                                    team1->getTrainer()->buffAnimal(team1->getAnimal(animalIndex1));
                                    break;
                                }

                                else{
                                    cout << "Invalid choice, please try again." << endl;
                                    continue;
                                }

                            break;
                        }

                        else{
                            cout << "Invalid choice, please try again." << endl;
                            continue;
                        }

                    }

                    cout << "Team " << team2->getTeamName() << "'s turn!" << endl; // Team 2's Turn

                    while(true){
                        cout << "Choose action:" << endl;
                        cout << "   1-) Animal" << endl;
                        cout << "   2-) Trainer" << endl;

                        cin >> choice;

                        if(choice == 1){

                            while(true){

                                cout << "Choose action:" << endl;
                                cout << "   1-) Attack" << endl;
                                cout << "   2-) Evade" << endl;

                                cin >> choice;

                                if(choice == 1){

                                    team2->getAnimal(animalIndex2)->performAttack(team1->getAnimal(animalIndex1));

                                    if(team1->getAnimal(animalIndex1)->getHealth() <= 0){
                                        cout << "Battle has ended! The winner is: " << team2->getTeamName() << endl; // Battle ends if opponent's health drops to 0.
                                        return;
                                    }
                                }

                                else if(choice == 2){
                                    Animal* a = team2->getAnimal(animalIndex2);

                                    if (Flyable* f = dynamic_cast<Flyable*>(a)) {
                                        f->fly();
                                    }

                                    if (Runnable* r = dynamic_cast<Runnable*>(a)) {
                                        r->run();
                                    }

                                    if (Swimmable* s = dynamic_cast<Swimmable*>(a)) {
                                        s->swim();
                                    }
                                }

                                else{
                                    cout << "Invalid choice, please try again." << endl;
                                    continue;
                                }


                                break;
                            }

                            break;
                        }

                        else if(choice == 2){

                            cout << "Choose action:" << endl;
                                cout << "   1-) Heal" << endl;
                                cout << "   2-) Buff" << endl;

                                cin >> choice;

                                if(choice == 1){

                                    team2->getTrainer()->healAnimal(team2->getAnimal(animalIndex2));
                                    break;
                                }

                                else if(choice == 2){

                                    team2->getTrainer()->buffAnimal(team2->getAnimal(animalIndex2));
                                    break;
                                }

                                else{
                                    cout << "Invalid choice, please try again." << endl;
                                    continue;
                                }

                            break;
                        }

                        else{
                            cout << "Invalid choice, please try again." << endl;
                            continue;
                        }

                    }

                }
            }

        }
};

//////////////////////////////////////////////////////////////////////////////////////////////////