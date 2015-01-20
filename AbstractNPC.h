#ifndef abstractnpc_INCLUDE
#define abstractnpc_INCLUDE

//Abstract base class: no implementation
//Base class for Monster Design Pattern
class AbstractNPC{
public:
	virtual void render() = 0; 
	virtual void renderAt(int x, int y) = 0;
	virtual int getHealth() = 0;
	virtual int getStrength() = 0;
	virtual int getRefreshRate() = 0;
	virtual int getDropRate() = 0;
	virtual void adjustXPos(int x) = 0;
	virtual void adjustYPos(int y) = 0;
	virtual int getXPos() = 0;
	virtual int getYPos() = 0;
	virtual void subtractHealth(int h) = 0;
	virtual ~AbstractNPC(){}

};

#endif //abstractnpc_INCLUDE