#include "MonsterManager.h"
#include "Champion.h"
#include "MonsterNPC.h"
#include "Brute.h"
#include "Fodder.h"
#include "Raider.h"
#include "Shaman.h"

void MonsterManager::init(){
	monster[0] = new Brute(new MonsterNPC("Brute", 512, 700));
	monster[1] = new Fodder(new MonsterNPC("Fodder", 700, 0));
	monster[2] = new Raider(new MonsterNPC("Raider", 300, 300));

	playerNPC = new Champion(new MonsterNPC("Champion", 100, 600));
}