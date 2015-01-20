#ifndef statecharacterscreen_INCLUDE
#define statecharacterscreen_INCLUDE

#include "Game.h"

//StateMainMenu inherits GameState class
class StateCharacterScreen :public GameState{
public:
	StateCharacterScreen(); //constructor
	virtual ~StateCharacterScreen(); //deconstructor

	virtual void init();
	virtual void draw(SDL_Window * window, Game &context); //draw the game state 
	virtual void handleEvent(SDL_Event const &sdlEvent, Game &context); //method to handle what state the game is at
	virtual void update(Game &context); //update the gamestate
	virtual void Cleanup(); //delete everything that is unused so that memory can be freed
	void displayMenuText(); //method to draw the menu text on the menu state
	virtual void enter(Game &context);

private:
	//pointers for the text displayed on the main menu
	Label* championLabel;
	Label* shamanLabel;

	TTF_Font* textFont;	// SDL type for True-Type font rendering

	int timeOfEnteredState;

};

#endif