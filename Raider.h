#ifndef raider_INCLUDE
#define raider_INCLUDE

#include "MonsterDecorator.h"

//Raider implements MonsterDecorator - all methods defined inline
class Raider : public MonsterDecorator{
public:
	virtual void render(){ MonsterDecorator::render(); }
	virtual void renderAt(int x, int y) { MonsterDecorator::renderAt(x, y); }
	virtual int getHealth() { return MonsterDecorator::getHealth(); }
	virtual int getStrength() { return MonsterDecorator::getStrength() + 3; }
	virtual int getRefreshRate(){ return MonsterDecorator::getRefreshRate() + 12; }
	virtual int getDropRate() { return MonsterDecorator::getDropRate() + 40; }
	virtual void adjustXPos(int x) { MonsterDecorator::adjustXPos(x); }
	virtual void adjustYPos(int y) { MonsterDecorator::adjustYPos(y); }
	virtual int getXPos() { return MonsterDecorator::getXPos(); }
	virtual int getYPos() { return MonsterDecorator::getYPos(); }

	//constructor
	Raider(AbstractNPC *n) : MonsterDecorator(n){}
	//deconstructor
	~Raider(){}

};

#endif //raider_INCLUDE