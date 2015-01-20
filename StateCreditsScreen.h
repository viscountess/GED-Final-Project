#ifndef statecreditsscreen_INCLUDE
#define statecreditsscreen_INCLUDE

#include "game.h"

class StateCreditsScreen :public GameState{

public:
	StateCreditsScreen(); //constructor
	virtual ~StateCreditsScreen(); //deconstructor

	virtual void init();
	virtual void draw(SDL_Window * window, Game &context); //draw the game state 
	virtual void handleEvent(SDL_Event const &sdlEvent, Game &context); //method to handle what state the game is at
	virtual void update(Game &context); //update the gamestate
	virtual void Cleanup(); //delete everything that is unused so that memory can be freed
	virtual void enter(Game &context);

private:

	TTF_Font* textFont;	// SDL type for True-Type font rendering

	//Labels
	Label* titleLabel;
	Label* nameLabel;

	float yOffset;

};


#endif