#include "Monster.h"

Monster::Monster(){}
Monster::Monster(string name, int currentHealth, int attack, int defense):GameCharacter(name,"Monster",currentHealth,attack,defense){

}
void Monster::triggerEvent(Object* player,Object* monster){
    Player* playerr = dynamic_cast<Player*>(player);
    Monster* monsterr = dynamic_cast<Monster*>(monster);
    char c;
    bool flag = true;
    cout << "Choose action:" << endl;
    cout << "A.Attack" << endl;
    cout << "B.Retreat" << endl;
    cin >> c;
    while(monsterr->getCurrentHealth()>0 && playerr->getCurrentHealth()>0 && flag==true){

    switch(c){
        case 'a': case 'A': cout << "You choose to attack" << endl;
                            cout << "Your attack does " << playerr->getAttack() << " damage" << endl;

                            monsterr->takeDamage(playerr->getAttack());

                            if(monsterr->checkIsDead()){
                                cout << "You beat the " << monsterr->getName() << endl;
                                if(monsterr->getName()!="boss"){
                                    cout << monsterr->getName() <<" drops a crystal" << endl;
                                    playerr->setCrystal(playerr->getCrystal()+1);
                                }
                            }

                            else{
                                cout << "Now the " << monsterr->getName() << " have " << monsterr->getCurrentHealth() << " health" << endl;
                                cout << "The " << monsterr->getName() << "'s attack does " << monsterr->getAttack()  << " damage" << endl;

                                playerr->takeDamage(monsterr->getAttack());

                                if(playerr->checkIsDead()){
                                    cout << "You dead" << endl;
                                    exit(0);
                                }
                                else{
                                    cout << "Now you have " << playerr->getCurrentHealth() << " health" << endl;
                                    cout << endl;
                                    cout << "Choose action:" << endl;
                                    cout << "A.Attack" << endl;
                                    cout << "B.Retreat" << endl;
                                    cin >> c;
                                    cout << endl;
                                }
                            }

                            break;

        case 'b': case 'B': playerr->changeRoom(playerr->getPreviousRoom());
                            flag = false;
                            break;
    }

    }
}
