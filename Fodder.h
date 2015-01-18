#ifndef fodder_INCLUDE
#define fodder_INCLUDE

#include "MonsterDecorator.h"

//Fodder implements MonsterDecorator - all methods defined inline
class Fodder : public MonsterDecorator{
public:
	virtual void render();
	virtual int getMana();
	virtual int getHealth();
	virtual int getStrength();
	virtual int getRefreshRate();
	virtual int getDropRate();

	//constructor
	Fodder();
	//deconstructor
	~Fodder();

#endif //fodder_INCLUDE