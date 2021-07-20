#include "Item.h"

Item::Item():Object(){}
Item::Item(string name,int health,int attack,int defense):Object(name,"Item"){
    this->health = health;
    this->attack = attack;
    this->defense = defense;
}
int Item::getHealth(){
    return this->health;
}
int Item::getAttack(){
    return this->attack;
}
int Item::getDefense(){
    return this->defense;
}
void Item::setHealth(int health){
    this->health = health;
}
void Item::setAttack(int attack){
    this->attack = attack;
}
void Item::setDefense(int defense){
    this->defense = defense;
}


void Item::triggerEvent(Object* player,Object* sword){
   cout << "You got the sword" << endl;
   Player* playerr = dynamic_cast<Player*>(player);
   Item* swordd = dynamic_cast<Item*>(sword);
   playerr->increaseStates(0,30,0);
   playerr->addItem(*swordd);
}
