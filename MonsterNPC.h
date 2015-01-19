#ifndef monsternpc_INCLUDE
#define monsternpc_INCLUDE

#include "AbstractNPC.h"
#include "Bitmap.h"
#include <string>

using std::string;

//MonsterNPC implements AbstractNPC with inline implementation
class MonsterNPC : public AbstractNPC{
public:
	virtual void render();
	virtual int getHealth() { return health; }
	virtual int getStrength() { return strength; }
	virtual int getRefreshRate() { return refreshRate; }
	virtual int getDropRate() { return dropRate; }

	//constructor
	MonsterNPC(char * basename);
	//deconstructor
	~MonsterNPC(){}

protected:
	int health;
	int strength;
	int refreshRate;
	int dropRate;

private:
	string name;

	//pointer member to image
	Bitmap *monster;
};

#endif //monsternpc_INCLUDE