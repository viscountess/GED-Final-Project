#ifndef shaman_INCLUDE
#define shaman_INCLUDE

#include "MonsterDecorator.h"

//Shaman implements MonsterDecorator - all methods defined inline
class Shaman : public MonsterDecorator{
public:
	virtual void render(){ MonsterDecorator::render(); }
	virtual void renderAt(int x, int y) { MonsterDecorator::renderAt(x, y); }
	virtual int getHealth() { return MonsterDecorator::getHealth(); }
	virtual int getStrength() { return MonsterDecorator::getStrength() + 10; }
	virtual int getRefreshRate(){ return MonsterDecorator::getRefreshRate() + 8000; }
	virtual int getDropRate() { return MonsterDecorator::getDropRate(); }
	virtual void adjustXPos(int x) { MonsterDecorator::adjustXPos(x); }
	virtual void adjustYPos(int y) { MonsterDecorator::adjustYPos(y); }
	virtual int getXPos() { return MonsterDecorator::getXPos(); }
	virtual int getYPos() { return MonsterDecorator::getYPos(); }
	virtual void subtractHealth(int h) { MonsterDecorator::subtractHealth(h); }

	//constructor
	Shaman(AbstractNPC *n) : MonsterDecorator(n) {}
	//deconstructor
	~Shaman(){}
};

#endif //shaman_INCLUDE