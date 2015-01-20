#ifndef monsternpc_INCLUDE
#define monsternpc_INCLUDE

#include "AbstractNPC.h"
#include "Bitmap.h"
#include "label.h"
#include <string>

using std::string;

//MonsterNPC implements AbstractNPC with inline implementation
class MonsterNPC : public AbstractNPC{
public:
	virtual void render();
	virtual void renderAt(int x, int y);
	virtual int getHealth() { return health; }
	virtual int getStrength() { return strength; }
	virtual int getRefreshRate() { return refreshRate; }
	virtual int getDropRate() { return dropRate; }
	virtual void adjustXPos(int x) { xpos += x; }
	virtual void adjustYPos(int y) { ypos += y; }
	virtual int getXPos() {return xpos; }
	virtual int getYPos() { return ypos; }
	virtual void subtractHealth(int h) { health -= h; if (health < 0) health = 0; }
	virtual void setHealth(int h){ health = h; }
	virtual void resetPosition(){ xpos = initialXpos, ypos = initialYpos; }
	//constructor
	MonsterNPC(char * basename, int x, int y);
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

	//member variables to be used for randomly positioning the monsters
	int xpos, ypos;

	int initialXpos, initialYpos;

	Label *healthLabel;

	TTF_Font* textFont;	// SDL type for True-Type font rendering
};

#endif //monsternpc_INCLUDE