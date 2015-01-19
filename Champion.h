#ifndef champion_INCLUDE
#define champion_INCLUDE

#include "MonsterDecorator.h"

//Champion implements MonsterDecorator - all methods defined inline
class Champion : public MonsterDecorator{
public:
	virtual void render(){ MonsterDecorator::render(); }
	virtual void renderAt(int x, int y) { MonsterDecorator::renderAt(x, y); }
	virtual int getHealth() { return MonsterDecorator::getHealth(); }
	virtual int getStrength() { return MonsterDecorator::getStrength() + 7; }
	virtual int getRefreshRate(){ return MonsterDecorator::getRefreshRate() + 3; }
	virtual int getDropRate() { return MonsterDecorator::getDropRate(); }
	virtual void adjustXPos(int x) { MonsterDecorator::adjustXPos(x); }
	virtual void adjustYPos(int y) { MonsterDecorator::adjustYPos(y); }
	virtual int getXPos() { return MonsterDecorator::getXPos(); }
	virtual int getYPos() { return MonsterDecorator::getYPos(); }

	//constructor
	Champion(AbstractNPC *n) : MonsterDecorator(n){}
	//deconstructor
	~Champion(){}
};

#endif //champion_INCLUDE