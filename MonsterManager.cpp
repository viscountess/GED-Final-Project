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

void MonsterManager::reset(){
	for (int i = 0; i < 3; i++)
	{
		monster[i]->setHealth(100);
		monster[i]->resetPosition();
	}
	playerNPC->setHealth(100);
	playerNPC->resetPosition();
}

bool MonsterManager::checkMonsterStillAlive(){

	//check to see if any monsters are alive
	for (int i = 0; i < 3; i++)
	{
		if (monster[i]->getHealth() > 0)
			return true;
	}
	return false;
}