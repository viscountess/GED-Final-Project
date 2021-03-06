#ifndef monsterdecorator_INCLUDE
#define monsterdecorator_INCLUDE

#include "AbstractNPC.h"

//MonsterNDecorator implements AbstractNPC - all methods defined inline
class MonsterDecorator : public AbstractNPC{
public:
	virtual void render(){ npc->render(); }
	virtual void renderAt(int x, int y) { npc->renderAt(x, y); }
	virtual int getHealth(){ return npc->getHealth(); }
	virtual int getStrength(){ return npc->getStrength(); }
	virtual int getRefreshRate(){ return npc->getRefreshRate(); }
	virtual int getDropRate(){ return npc->getDropRate(); }
	virtual void adjustXPos(int x) { npc->adjustXPos(x); }
	virtual void adjustYPos(int y) { npc->adjustYPos(y); }
	virtual int getXPos() { return npc->getXPos(); }
	virtual int getYPos() { return npc->getYPos(); }
	virtual void subtractHealth(int h) { npc->subtractHealth(h); }
	virtual void setHealth(int h){ npc->setHealth(h); }
	virtual void resetPosition(){ npc->resetPosition(); }

	//constructor
	MonsterDecorator(AbstractNPC *n) { npc = n; }
	//deconstructor
	~MonsterDecorator(){}

private:
	AbstractNPC *npc;
};
#endif //monsterdecorator_INCLUDE