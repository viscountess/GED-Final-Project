#ifndef brute_INCLUDE
#define brute_INCLUDE

#include "MonsterDecorator.h"

//Brute implements MonsterDecorator - all methods defined inline
class Brute : public MonsterDecorator{
public:
	virtual void render(){ MonsterDecorator::render(); }
	virtual void renderAt(int x, int y) { MonsterDecorator::renderAt(x, y); }
	virtual int getHealth() { return MonsterDecorator::getHealth(); }
	virtual int getStrength() { return MonsterDecorator::getStrength() + 5; }
	virtual int getRefreshRate(){ return MonsterDecorator::getRefreshRate() + 6000; }
	virtual int getDropRate() { return MonsterDecorator::getDropRate() + 15; }
	virtual void adjustXPos(int x) { MonsterDecorator::adjustXPos(x); }
	virtual void adjustYPos(int y) { MonsterDecorator::adjustYPos(y); }
	virtual int getXPos() { return MonsterDecorator::getXPos(); }
	virtual int getYPos() { return MonsterDecorator::getYPos(); }
	virtual void subtractHealth(int h) { MonsterDecorator::subtractHealth(h); }

	//constructor
	Brute(AbstractNPC *n) : MonsterDecorator(n){}
	//deconstructor
	~Brute(){}
};

#endif //brute_INCLUDE