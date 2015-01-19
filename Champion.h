#ifndef champion_INCLUDE
#define champion_INCLUDE

#include "MonsterDecorator.h"

//Champion implements MonsterDecorator - all methods defined inline
class Champion : public MonsterDecorator{
public:
	virtual void render(){ MonsterDecorator::render(); }
	virtual int getHealth() { return MonsterDecorator::getHealth(); }
	virtual int getStrength() { return MonsterDecorator::getStrength() + 7; }
	virtual int getRefreshRate(){ return MonsterDecorator::getRefreshRate() + 3; }
	virtual int getDropRate() { return MonsterDecorator::getDropRate(); }

	//constructor
	Champion(AbstractNPC *n) : MonsterDecorator(n){}
	//deconstructor
	~Champion(){}
};

#endif //champion_INCLUDE