#ifndef monsterdecorator_INCLUDE
#define monsterdecorator_INCLUDE

#include "AbstractNPC.h"

//MonsterNDecorator implements AbstractNPC - all methods defined inline
class MonsterDecorator : public AbstractNPC{
public:
	virtual void render(){ npc->render(); }
	virtual int getHealth(){ return npc->getHealth(); }
	virtual int getStrength(){ return npc->getStrength(); }
	virtual int getRefreshRate(){ return npc->getRefreshRate(); }
	virtual int getDropRate(){ return npc->getDropRate(); }

	//constructor
	MonsterDecorator(AbstractNPC *n) { npc = n; }
	//deconstructor
	~MonsterDecorator(){}

private:
	AbstractNPC *npc;
};
#endif //monsterdecorator_INCLUDE