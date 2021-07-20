#include "Player.h"

Player::Player(){}
Player::Player(string name,int currentHealth,int attack,int defense,int crystal):GameCharacter(name,"Player",currentHealth,attack,defense){
    this->crystal = crystal;
}
void Player::addItem(Item item){
    inventory.push_back(item);
}
void Player::increaseStates(int health,int attack,int defense){
    setCurrentHealth(getCurrentHealth() + health);
    setAttack(getAttack() + attack);
    setDefense(getDefense() + defense);
}
void Player::changeRoom(Room* changeRoom){
    setPreviousRoom(getCurrentRoom());
    setCurrentRoom(changeRoom);
}

void Player::setCurrentRoom(Room* currentRoom){
    this->currentRoom = currentRoom;
}
void Player::setPreviousRoom(Room* previousRoom){
    this->previousRoom = previousRoom;
}
void Player::setInventory(vector<Item> inventory){
    for(int i=0;i<inventory.size();i++){
        this->inventory.push_back(inventory[i]);
    }
}
//crystal
void Player::setCrystal(int crystal){
    this->crystal = crystal;
}
int Player::getCrystal(){
    return this->crystal;
}


Room* Player::getCurrentRoom(){
    return this->currentRoom;
}
Room* Player::getPreviousRoom(){
    return this->previousRoom;
}
vector<Item> Player::getInventory(){
    return this->inventory;
}

void Player::triggerEvent(Object* player,Object* player2){

    cout << "Status: " << endl;
    cout << "[" << player->getName() << "]" << endl;

    Player* playerr = dynamic_cast<Player*>(player);

    cout << "Health: " << playerr->getCurrentHealth() << "/" << playerr->getMaxHealth() << endl;
    cout << "Attack: " << playerr->getAttack() << endl;
    cout << "Defense: " << playerr->getDefense() << endl;
    cout << "Crystal: " << playerr->getCrystal() << endl;
    cout << "Inventory: ";
    for(int i=0;i<inventory.size();i++){
        cout << playerr->getInventory()[i].getName() << ", ";
    }
    cout << endl;

}
