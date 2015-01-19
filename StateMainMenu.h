#ifndef statemainmenu_INCLUDE
#define statemainmenu_INCLUDE

#include "Game.h"

//StateMainMenu inherits GameState class
class StateMainMenu :public GameState{
public:
	StateMainMenu(); //constructor
	virtual ~StateMainMenu(); //deconstructor

	virtual void init();
	virtual void draw(SDL_Window * window, Game &context); //draw the game state 
	virtual void handleEvent(SDL_Event const &sdlEvent, Game &context); //method to handle what state the game is at
	virtual void update(Game &context); //update the gamestate
	virtual void Cleanup(); //delete everything that is unused so that memory can be freed
	void displayMenuText(); //method to draw the menu text on the menu state
	virtual void enter(){}

private:
	//pointers for the text displayed on the main menu
	Label* playLabel;
	Label* quitLabel;
	Label* creditLabel;


	TTF_Font* textFont;	// SDL type for True-Type font rendering

	Label* currentSelection;

	//functions to handle the menu select functions
	void handleUPpress();
	void handleDOWNpress();
	void handleENTERpress(Game &context);

	//function to quickly change the colour of the menu buttons
	void setupLabels(SDL_Color playColor, SDL_Color creditsColor, SDL_Color quitColor);
};

#endif