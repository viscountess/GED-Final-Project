#ifndef champion_INCLUDE
#define champion_INCLUDE

#include "MonsterDecorator.h"

//Champion implements MonsterDecorator - all methods defined inline
class Champion : public MonsterDecorator{
public:
	virtual void render();
	virtual int getMana();
	virtual int getHealth();
	virtual int getStrength();
	virtual int getRefreshRate();
	virtual int getDropRate();

	//constructor
	Champion();
	//deconstructor
	~Champion();

#endif //champion_INCLUDE