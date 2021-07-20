#include <iostream>
#include <string>
#include <vector>
#include "Item.h"
#include "Dungeon.h"
#include "Monster.h"
#include "NPC.h"
#include "Player.h"
using namespace std;

int main()
{

    Dungeon dungeon = Dungeon();
    dungeon.runDungeon();


    return 0;
}
