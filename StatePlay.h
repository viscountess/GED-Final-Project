#ifndef stateplay_INCLUDE
#define stateplay_INCLUDE

#include "Game.h"
#include "AbstractNPC.h"

//StatePlay inherits GameState class
class StatePlay:public GameState{
public:
	StatePlay(); //constructor
	virtual ~StatePlay(); //deconstructor

	virtual void init();
	virtual void draw(SDL_Window * window); //draw the game state 
	virtual void handleEvent(SDL_Event const &sdlEvent, Game &context); //method to handle what state the game is at
	virtual void update(Game &context); //update the gamestate
	virtual void Cleanup(); //delete everything that is unused so that memory can be freed
	virtual void enter(){}

private:

	clock_t lastTime; // clock_t is an integer type
	clock_t currentTime; // use this to track time between frames

	TTF_Font* textFont;	// SDL type for True-Type font rendering

	//member pointer for monster class
	//three monsters to appear on the map
	AbstractNPC *monster[3];

	//two player monsters to appear on screen
	AbstractNPC *playerNPC[2];
};

#endif