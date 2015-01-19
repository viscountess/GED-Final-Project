#ifndef fodder_INCLUDE
#define fodder_INCLUDE

#include "MonsterDecorator.h"

//Fodder implements MonsterDecorator - all methods defined inline
class Fodder : public MonsterDecorator{
public:
	virtual void render(){ MonsterDecorator::render(); }
	virtual void renderAt(int x, int y) { MonsterDecorator::renderAt(x, y); }
	virtual int getHealth() { return MonsterDecorator::getHealth(); }
	virtual int getStrength() { return MonsterDecorator::getStrength() + 3; }
	virtual int getRefreshRate(){ return MonsterDecorator::getRefreshRate() + 7; }
	virtual int getDropRate() { return MonsterDecorator::getDropRate() + 5; }
	virtual void adjustXPos(int x) { MonsterDecorator::adjustXPos(x); }
	virtual void adjustYPos(int y) { MonsterDecorator::adjustYPos(y); }
	virtual int getXPos() { return MonsterDecorator::getXPos(); }
	virtual int getYPos() { return MonsterDecorator::getYPos(); }

	//constructor
	Fodder(AbstractNPC *n) : MonsterDecorator(n){}
	//deconstructor
	~Fodder(){}
};

#endif //fodder_INCLUDE