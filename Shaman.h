#ifndef shaman_INCLUDE
#define shaman_INCLUDE

#include "MonsterDecorator.h"

//Shaman implements MonsterDecorator - all methods defined inline
class Shaman : public MonsterDecorator{
public:
	virtual void render();
	virtual int getMana();
	virtual int getHealth();
	virtual int getStrength();
	virtual int getRefreshRate();
	virtual int getDropRate();

	//constructor
	Shaman();
	//deconstructor
	~Shaman();
};

#endif //shaman_INCLUDE