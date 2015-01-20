#ifndef monstermanager_INCLUDE
#define monstermanager_INCLUDE

#include"AbstractNPC.h"

//This class is being used to keep track of the monsters used between states
class MonsterManager{
public:
	MonsterManager(){}
	~MonsterManager(){}

	void init();
	void reset();

	AbstractNPC *getMonster(int m){ return monster[m]; }
	AbstractNPC *getPlayer() { return playerNPC; }

	AbstractNPC *getBattleMonster(){ return battleMonster; }
	void setBattleMonsterIndex(int m){ battleMonster = monster[m]; }

	bool checkMonsterStillAlive();

private:
	//member pointer for monster class
	//three monsters to appear on the map
	AbstractNPC *monster[3];

	//two player monsters to appear on screen
	AbstractNPC *playerNPC;

	//pointer variable to current monster the player is fighting
	AbstractNPC *battleMonster;

};
#endif