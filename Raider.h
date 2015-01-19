#ifndef raider_INCLUDE
#define raider_INCLUDE

#include "MonsterDecorator.h"

//Raider implements MonsterDecorator - all methods defined inline
class Raider : public MonsterDecorator{
public:
	virtual void render(){ MonsterDecorator::render(); }
	virtual int getHealth() { return MonsterDecorator::getHealth(); }
	virtual int getStrength() { return MonsterDecorator::getStrength() + 3; }
	virtual int getRefreshRate(){ return MonsterDecorator::getRefreshRate() + 12; }
	virtual int getDropRate() { return MonsterDecorator::getDropRate() + 40; }

	//constructor
	Raider(AbstractNPC *n) : MonsterDecorator(n){}
	//deconstructor
	~Raider(){}

};

#endif //raider_INCLUDE