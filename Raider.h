#ifndef raider_INCLUDE
#define raider_INCLUDE

#include "MonsterDecorator.h"

//Raider implements MonsterDecorator - all methods defined inline
class Raider : public MonsterDecorator{
public:
	virtual void render();
	virtual int getMana();
	virtual int getHealth();
	virtual int getStrength();
	virtual int getRefreshRate();
	virtual int getDropRate();

	//constructor
	Raider();
	//deconstructor
	~Raider();

#endif //raider_INCLUDE