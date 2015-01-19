#ifndef brute_INCLUDE
#define brute_INCLUDE

#include "MonsterDecorator.h"

//Brute implements MonsterDecorator - all methods defined inline
class Brute : public MonsterDecorator{
public:
	virtual void render(){ MonsterDecorator::render(); }
	virtual int getHealth() { return MonsterDecorator::getHealth(); }
	virtual int getStrength() { return MonsterDecorator::getStrength() + 5; }
	virtual int getRefreshRate(){ return MonsterDecorator::getRefreshRate() + 6; }
	virtual int getDropRate() { return MonsterDecorator::getDropRate() + 15; }
	virtual void adjustXPos(int x) { MonsterDecorator::adjustXPos(x); }
	virtual void adjustYPos(int y) { MonsterDecorator::adjustYPos(y); }

	//constructor
	Brute(AbstractNPC *n) : MonsterDecorator(n){}
	//deconstructor
	~Brute(){}
};

#endif //brute_INCLUDE