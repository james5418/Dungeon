#include "Dungeon.h"
#include <iostream>

using namespace std ;
void saveToFile(Player*, vector<Room>&);
void loadFromFile(string,Player*, vector<Room>&);
Record record;
Dungeon::Dungeon(){}

string playername;

vector<Object*> room_0_object,room_1_object,room_2_object,room_3_object,room_4_object,room_5_object,room_6_object,room_7_object;

Item sword("sword",0,30,0),EX_curry_stick("EX_curry_stick",0,10000,0),potion("potion",100,0,0);

vector<Item> commodity_villager{EX_curry_stick},commodity_trader{potion};

vector<Item> player_inventory;

string script_villager = "villager: Hello! Can you help me collect three crystal? I will give you the EX curry stick for helping me.";
string script_trader = "trader: Do you want to buy something?";

NPC villager("villager",script_villager,commodity_villager);
NPC trader("trader",script_trader,commodity_trader);


Monster slime("slime",30,1,0),goblin("goblin",60,10,0),boss("boss",1000,1000,1000);



void Dungeon::createPlayer(){
    player.setName(playername);
    player.setMaxHealth(100);
    player.setCurrentHealth(100);
    player.setAttack(0);
    player.setDefense(30);
    player.setCurrentRoom(&rooms[0]);
    player.setInventory(player_inventory);
    player.setTag("Player");
    player.setCrystal(0);



    //villager.setName("villager");
    //villager.setScript(script_villager);
    //villager.setCommodity(commodity_villager);
    //trader.setName("trader");
    //trader.setScript(script_trader);
    //trader.setCommodity(commodity_trader);


}


void Dungeon::createMap(){

    room_0_object.push_back(nullptr);
    room_1_object.push_back(&sword);
    room_2_object.push_back(&villager);
    room_3_object.push_back(nullptr);
    room_4_object.push_back(&goblin);
    room_5_object.push_back(&slime);
    room_6_object.push_back(&trader);
    room_7_object.push_back(&boss);


    rooms.push_back(Room(false,0,room_0_object)) ;
    rooms.push_back(Room(false,1,room_1_object)) ;
    rooms.push_back(Room(false,2,room_2_object)) ;
    rooms.push_back(Room(false,3,room_3_object)) ;
    rooms.push_back(Room(false,4,room_4_object)) ;
    rooms.push_back(Room(false,5,room_5_object)) ;
    rooms.push_back(Room(false,6,room_6_object)) ;
    rooms.push_back(Room(true,7,room_7_object)) ;


    rooms[0].setUpRoom(&rooms[1]);
    rooms[0].setDownRoom(nullptr);
    rooms[0].setLeftRoom(nullptr);
    rooms[0].setRightRoom(nullptr);

    rooms[1].setUpRoom(&rooms[2]);
    rooms[1].setDownRoom(&rooms[0]);
    rooms[1].setLeftRoom(nullptr);
    rooms[1].setRightRoom(&rooms[5]);
    rooms[1].setObjects(room_1_object);

    rooms[2].setUpRoom(nullptr);
    rooms[2].setDownRoom(&rooms[1]);
    rooms[2].setLeftRoom(&rooms[3]);
    rooms[2].setRightRoom(nullptr);
    rooms[2].setObjects(room_2_object);

    rooms[3].setUpRoom(nullptr);
    rooms[3].setDownRoom(&rooms[4]);
    rooms[3].setLeftRoom(nullptr);
    rooms[3].setRightRoom(&rooms[2]);
    rooms[3].setObjects(room_3_object);

    rooms[4].setUpRoom(&rooms[3]);
    rooms[4].setDownRoom(nullptr);
    rooms[4].setLeftRoom(nullptr);
    rooms[4].setRightRoom(nullptr);
    rooms[4].setObjects(room_4_object);

    rooms[5].setUpRoom(&rooms[6]);
    rooms[5].setDownRoom(nullptr);
    rooms[5].setLeftRoom(&rooms[1]);
    rooms[5].setRightRoom(nullptr);
    rooms[5].setObjects(room_5_object);

    rooms[6].setUpRoom(nullptr);
    rooms[6].setDownRoom(&rooms[5]);
    rooms[6].setLeftRoom(nullptr);
    rooms[6].setRightRoom(&rooms[7]);
    rooms[6].setObjects(room_6_object);

    rooms[7].setUpRoom(nullptr);
    rooms[7].setDownRoom(nullptr);
    rooms[7].setLeftRoom(&rooms[6]);
    rooms[7].setRightRoom(nullptr);
    rooms[7].setObjects(room_7_object);

}


void Dungeon::handleMovement(){
    char enter;
    cout << "Where do you want to go?" << endl;

    cout << "You are in room " << player.getCurrentRoom()->getIndex() <<endl;

    if(player.getCurrentRoom()->getUpRoom() != nullptr){
        cout << "U. Go up" << endl;
    }
    if(player.getCurrentRoom()->getDownRoom() != nullptr){
        cout << "D. Go down" << endl;
    }
    if(player.getCurrentRoom()->getLeftRoom() != nullptr){
        cout << "L. Go left" << endl;
    }
    if(player.getCurrentRoom()->getRightRoom() != nullptr){
        cout << "R. Go right" << endl;
    }

    cin >> enter;
    cout << endl;
    switch (enter){
        case 'u' : case 'U' : player.changeRoom(player.getCurrentRoom()->getUpRoom());
                              break;
        case 'd' : case 'D' : player.changeRoom(player.getCurrentRoom()->getDownRoom());
                              break;
        case 'l' : case 'L' : player.changeRoom(player.getCurrentRoom()->getLeftRoom());
                              break;
        case 'r' : case 'R' : player.changeRoom(player.getCurrentRoom()->getRightRoom());
                              break;
    }

}


void Dungeon::handleEvent(Object* player){
    Player* playerr = dynamic_cast<Player*>(player);

    if(playerr->getCurrentRoom()->getIndex() == 1){
        sword.triggerEvent(player,&sword);
    }
    else if(playerr->getCurrentRoom()->getIndex() == 2){
        villager.triggerEvent(player,&villager);
    }
    else if(playerr->getCurrentRoom()->getIndex() == 6){
        trader.triggerEvent(player,&trader);
    }
    else if(playerr->getCurrentRoom()->getIndex() == 5){
        slime.triggerEvent(player,&slime);
    }
    else if(playerr->getCurrentRoom()->getIndex() == 4){
        goblin.triggerEvent(player,&goblin);
    }
    else if(playerr->getCurrentRoom()->getIndex() == 7){
        boss.triggerEvent(player,&boss);
    }
}


void Dungeon::startGame(){
    cout << "Please enter player's name: ";
    cin >> playername;
    cout << endl;
    createMap();
    createPlayer();

    while(checkGameLogic()){

        chooseAction();

        if(boss.getCurrentHealth() <= 0){
            cout << "Congratulation! You win!" << endl;
            exit(0);
        }

    }


}


void Dungeon::chooseAction(){

    if(player.getCurrentRoom()->getIndex()!=3 && player.getCurrentRoom()->getIndex()!=0){
        char d;
        cout << "What do you want to do?" << endl;
        cout << "A.Move" << endl;
        cout << "B.Check Status" << endl;
        cout << "C.Save to file" << endl;

        if(player.getCurrentRoom()->getIndex()==1 && player.getAttack()<30){
            cout << "D.Open the chest" << endl;
        }
        if(player.getCurrentRoom()->getIndex()==2){
            cout << "D.Talk to villager" << endl;
        }
        if(player.getCurrentRoom()->getIndex()==4 && goblin.getCurrentHealth()>0){
            cout << "D.Fight with goblin" << endl;
        }
        if(player.getCurrentRoom()->getIndex()==5 && slime.getCurrentHealth()>0){
            cout << "D.Fight with slime" << endl;
        }
        if(player.getCurrentRoom()->getIndex()==6){
            cout << "D.Talk to trader" << endl;
        }
        if(player.getCurrentRoom()->getIndex()==7 && boss.getCurrentHealth()>0){
            cout << "D.Fight with boss" << endl;
        }


        cin >> d;
        cout << endl;
        switch(d){
            case 'a' : case 'A' : handleMovement();
                                  break;
            case 'b' : case 'B' : player.triggerEvent(&player,&player);
                                  break;
            case 'c' : case 'C' : record.saveToFile(&player,rooms);
                                  break;
            case 'd' : case 'D' : handleEvent(&player);
                                  break;
        }
    }

    else if(player.getCurrentRoom()->getIndex()==3 && player.getPreviousRoom()->getIndex()==2){
        char d;
        cout << "You find a crystal" << endl;
        player.setCrystal(player.getCrystal()+1);
        cout << "What do you want to do?" << endl;
        cout << "A.Move" << endl;
        cout << "B.Check Status" << endl;
        cout << "C.Save to file" << endl;

        cin >> d;
        cout << endl;
        switch(d){
            case 'a' : case 'A' : handleMovement();
                                  break;
            case 'b' : case 'B' : player.triggerEvent(&player,&player);
                                  break;
            case 'c' : case 'C' : record.saveToFile(&player,rooms);
                                  break;

        }
    }
    else{
        char d;

        cout << "What do you want to do?" << endl;
        cout << "A.Move" << endl;
        cout << "B.Check Status" << endl;
        cout << "C.Save to file" << endl;

        cin >> d;
        cout << endl;
        switch(d){
            case 'a' : case 'A' : handleMovement();
                                  break;
            case 'b' : case 'B' : player.triggerEvent(&player,&player);
                                  break;
            case 'c' : case 'C' : record.saveToFile(&player,rooms);
                                  break;
        }
    }

}


bool Dungeon::checkGameLogic(){
    if(player.checkIsDead() || boss.getCurrentHealth() <= 0){
        return false;
    }
    else{
        return true;
    }
}




void Dungeon::runDungeon(){
    char enter;
    cout << "Do you want to load previous data?" << endl;
    cout << "a.Yes" << endl;
    cout << "b.No. Start new game" << endl;
    cin >> enter;
    cout << endl;

    switch(enter){
        case 'a' : case 'A' : record.loadFromFile(player.getName(),&player,rooms);
                            while(checkGameLogic()){

                                chooseAction();

                                if(boss.getCurrentHealth() <= 0){
                                    cout << "Congratulation! You win!" << endl;
                                    exit(0);
                                }

                            }
                              break;
        case 'b' : case 'B' :startGame();
                              break;
    }
}
