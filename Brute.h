#ifndef brute_INCLUDE
#define brute_INCLUDE

#include "MonsterDecorator.h"

//Brute implements MonsterDecorator - all methods defined inline
class Brute : public MonsterDecorator{
public:
	virtual void render();
	virtual int getMana();
	virtual int getHealth();
	virtual int getStrength();
	virtual int getRefreshRate();
	virtual int getDropRate();

	//constructor
	Brute();
	//deconstructor
	~Brute();

#endif //brute_INCLUDE