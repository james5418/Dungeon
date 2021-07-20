#include "Record.h"
#include <unistd.h>

Record::Record(){}

void Record::savePlayer(Player* now, ofstream& out){

    out << now->getTag() << ' ' << now->getName() << ' ' <<  now->getCrystal() << endl; ;

    out << now->getMaxHealth() << ' ' << now->getCurrentHealth() << ' ';
    out << now->getAttack() << ' ' << now-> getDefense() << '\n';

    Room* cur = now->getCurrentRoom();
    Room* prv = now->getPreviousRoom();

    out << cur->getIndex() << ' ';
    out << prv->getIndex() << '\n';

    vector<Item> inventory = now->getInventory();
    out << inventory.size() << '\n';
    for(int i=0;i<inventory.size();i++){
        out << inventory[i].getTag() << ' ';
        out << inventory[i].getName() << '\n';
        out << inventory[i].getHealth() << ' ';
        out << inventory[i].getAttack() << ' ';
        out << inventory[i].getDefense() << '\n';

    }
}


void Record::loadPlayer(Player* now, ifstream& in, vector<Room>& rooms){
    string tag,nam;
    int mh,ch,att,df,cy;
    in >> tag >> nam >> cy;
    in >> mh >> ch >> att >> df;
    *now = *(new Player(nam,ch,att,df,cy));
    now->setMaxHealth(mh);
    int curRoomid;
    in >> curRoomid;
    int prvRoomid;
    in >> prvRoomid;
    now->setCurrentRoom(&rooms[curRoomid]);
    now->setPreviousRoom(&rooms[prvRoomid]);
    vector<Item> inventory;
    int t;
    in >> t;
    while(t--){
        in >> tag >> nam;
        int h,a,d;
        in >> h >> a >> d;
        inventory.push_back(Item(nam,h,a,d));
    }
    now-> setInventory(inventory);
}

void Record::saveRooms(vector<Room>& v, ofstream& out){
    out << v.size() << '\n';
    for(int i=0;i<v.size();i++){
        out << (v[i].getIsExit() ? true:false) << '\n';

        out << (v[i].getUpRoom()==NULL ? -1 : (v[i].getUpRoom())->getIndex()) << ' ';
        out << (v[i].getDownRoom()==NULL ? -1 : (v[i].getDownRoom())->getIndex()) << ' ';
        out << (v[i].getLeftRoom()==NULL ? -1 : (v[i].getLeftRoom())->getIndex()) << ' ';
        out << (v[i].getRightRoom()==NULL ? -1 : (v[i].getRightRoom())->getIndex()) << '\n';


        vector<Object*> vv = v[i].getObjects();

        if(vv[0] == nullptr){
            out << 0 << endl;
            continue;
        }
        else{
            out << 1 << endl;

            out << vv[0]->getName() << endl;

            if(vv[0]->getName()=="slime" || vv[0]->getName()=="goblin" || vv[0]->getName()=="boss"){
                Monster* monster = dynamic_cast<Monster*>(vv[0]);
                out << monster->getCurrentHealth() << ' ' << monster->getAttack() << ' ' << monster->getDefense() << endl;
            }
            if(vv[0]->getName()=="trader" || vv[0]->getName()=="villager"){
                NPC* npc = dynamic_cast<NPC*>(vv[0]);
                out << npc->getScript() << endl;
                out << npc->getCommodity()[0].getName() << ' ' << npc->getCommodity()[0].getTag() << endl;
                out << npc->getCommodity()[0].getHealth() << ' ' << npc->getCommodity()[0].getAttack() << ' ' << npc->getCommodity()[0].getDefense() << endl;
            }
            if(vv[0]->getName()=="sword"){
                Item* item = dynamic_cast<Item*>(vv[0]);
                out << item->getHealth() << ' ' << item->getAttack() << ' ' << item->getDefense() << endl;
            }
        }
    }
}

void Record::loadRooms(vector<Room>& v, ifstream& in){
    int n;
    in >> n;
    for(int i=0; i<n; i++){
        v.push_back(Room());
        v[i].setIndex(i);
    }
    for(int i=0;i<n;i++){
        int isExit;
        in >> isExit;
        v[i].setIsExit((isExit == true ? true:false));



        int up,dw,lf,rg;
        in >> up >> dw >> lf >> rg;
        if(up != -1){
            v[i].setUpRoom(&v[up]);
        }
        else if(up == -1){
            v[i].setUpRoom(nullptr);
        }
        if(dw != -1){
            v[i].setDownRoom(&v[dw]);
        }
        else if(dw == -1){
            v[i].setDownRoom(nullptr);
        }
         if(lf != -1){
            v[i].setLeftRoom(&v[lf]);
        }
        else if(lf == -1){
            v[i].setLeftRoom(nullptr);
        }
         if(rg != -1){
            v[i].setRightRoom(&v[rg]);
        }
        else if(rg == -1){
            v[i].setRightRoom(nullptr);
        }


        vector<Object*> objs;
        objs.clear();
        int x;
        in >> x;
        if(x==0){
            continue;
        }
        else if(x == 1){

            string nam;
            in >>  nam;
            if(nam == "slime" || nam == "goblin" || nam == "boss"){
                int cth,att,def;
                in >> cth >> att >> def;
                objs.push_back(new Monster(nam,cth,att,def));

            }
            if(nam=="trader" || nam=="villager"){
                in.ignore();
                string scr;
                getline(in,scr);
                vector<Item> comm;
                comm.clear();

                string itnam,ittag;
                in >> itnam >> ittag;
                int h,a,d;
                in >> h >> a >> d;

                comm.push_back(Item(itnam, h, a, d));

                //NPC* npc = new NPC();
                //npc->setName(nam);
                //npc->setScript(scr);
                //npc->setCommodity(comm);
                //objs.push_back(npc);
                objs.push_back(new NPC(nam, scr, comm));

            }
            if(nam=="sword"){
                int h,a,d;
                in >> h >> a >> d;
                objs.push_back(new Item(nam,h,a,d));
            }

            v[i].setObjects(objs);

        }

    }
}





void Record::saveToFile(Player* now, vector<Room>& v){

    std::ofstream out;
    out.open("map.txt");
    this->saveRooms(v,out);
    out.close();

    out.open("usr.txt");
    this->savePlayer(now,out);
    out.close();
    cout  << endl << "Record saved" << endl;
}

void Record::loadFromFile(string nam, Player* now, vector<Room>& v) {
    std::ifstream file_in;
    cout << "Map ........ ";
    file_in.open("map.txt");
    loadRooms(v,file_in);
    file_in.close();
    sleep(1);
    cout << "Finished" << endl;

    cout << "User ....... ";
    file_in.open("usr.txt");
	loadPlayer(now, file_in, v);
	file_in.close();
	sleep(1);
	cout << "Finished\n";
}

bool Record::checkFile(string nam){
    std::ifstream file_in;

    string file_name = "usr.txt";
    file_in.open(file_name);

    if(!file_in.good()){
        return false;
    }
    file_in.close();

    file_name = "map.txt";
    file_in.open(file_name);
    if(!file_in.good()){
        return false;
    }
    file_in.close();

    return true;
}
