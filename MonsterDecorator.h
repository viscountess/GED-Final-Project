#ifndef monsterdecorator_INCLUDE
#define monsterdecorator_INCLUDE

#include "AbstractNPC.h"

//MonsterNPC implements AbstractNPC - all methods defined inline
class MonsterDecorator : public AbstractNPC{
public:
	virtual void render();
	virtual int getMana();
	virtual int getHealth();
	virtual int getStrength();
	virtual int getRefreshRate();
	virtual int getDropRate();
};
#endif //monsterdecorator_INCLUDE