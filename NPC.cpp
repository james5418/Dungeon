#include "NPC.h"

NPC::NPC(){}
NPC::NPC(string name, string script, vector<Item> commodity):GameCharacter(name,"NPC",1,1,1){
    this->script = script;
    for(int i = 0;i<commodity.size();i++){
        this->commodity.push_back(commodity[i]);
    }

}

void NPC::listCommodity(){
    for(int i=0;i<commodity.size();i++){
        cout << commodity[i].getName() << endl;
    }
}
void NPC::setScript(string script){
    this->script = script;
}
void NPC::setCommodity(vector<Item> commodity){
    for(int i = 0;i<commodity.size();i++){
        this->commodity.push_back(commodity[i]);
    }
}
string NPC::getScript(){
    return this->script;
}
vector<Item> NPC::getCommodity(){
    return this->commodity;
}

void NPC::triggerEvent(Object* player,Object* npc){
    Player* playerr = dynamic_cast<Player*>(player);
    NPC* npcc = dynamic_cast<NPC*>(npc);

    cout << npcc->getScript() << endl;

    if(npcc->getName()=="trader"){
        char c;
        cout << "A.potion(top up your health to 100)" << endl;
        cout << "B.No thanks" << endl;
        cin >> c;
        cout << endl;
        switch(c){
            case 'a': case 'A': cout << "You got a potion" << endl;
                                playerr->setCurrentHealth(100);
                                playerr->addItem(npcc->getCommodity()[0]);
                                break;

            case 'b': case 'B': cout << "trader: Good bye" << endl;
                                break;
        }

    }
    else if(npcc->getName()=="villager"){

        if(playerr->getCrystal()>=3){

            cout << "villager: Thanks a lot!" << endl;
            cout << "You got the EX curry stick" << endl;
            playerr->increaseStates(0,10000,0);
            playerr->addItem(npcc->getCommodity()[0]);
        }
    }


}
