#ifndef monsternpc_INCLUDE
#define monsternpc_INCLUDE

#include "AbstractNPC.h"

//MonsterNPC implements AbstractNPC - all methods defined inline
class MonsterNPC : public AbstractNPC{
public:
	virtual void render();
	virtual int getMana();
	virtual int getHealth();
	virtual int getStrength();
	virtual int getRefreshRate();
	virtual int getDropRate();

	//constructor
	MonsterNPC();
	//deconstructor
	~MonsterNPC();
};

#endif //monsternpc_INCLUDE