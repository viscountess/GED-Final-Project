#ifndef shaman_INCLUDE
#define shaman_INCLUDE

#include "MonsterDecorator.h"

//Shaman implements MonsterDecorator - all methods defined inline
class Shaman : public MonsterDecorator{
public:
	virtual void render(){ MonsterDecorator::render(); }
	virtual int getHealth() { return MonsterDecorator::getHealth(); }
	virtual int getStrength() { return MonsterDecorator::getStrength() + 10; }
	virtual int getRefreshRate(){ return MonsterDecorator::getRefreshRate() + 8; }
	virtual int getDropRate() { return MonsterDecorator::getDropRate(); }

	//constructor
	Shaman(AbstractNPC *n) : MonsterDecorator(n) {}
	//deconstructor
	~Shaman(){}
};

#endif //shaman_INCLUDE