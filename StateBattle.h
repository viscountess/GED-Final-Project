#ifndef statebattle_INCLUDE
#define statebattle_INCLUDE
#include "game.h"

class StateBattle : public GameState{
public:
	StateBattle(){}
	~StateBattle(){}
	virtual void init();
	virtual void draw(SDL_Window * window, Game &context); //draw the game state 
	virtual void handleEvent(SDL_Event const &sdlEvent, Game &context); //method to handle what state the game is at
	virtual void update(Game &context); //update the gamestate
	virtual void Cleanup(); //delete everything that is unused so that memory can be freed
	virtual void enter(Game &context);

private:
	int attackTime[2];
	int attackDelay[2];

	int dmgTaken; //member variable to store how much damage has been taken
};
#endif