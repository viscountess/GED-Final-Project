#ifndef statesplashscreen_INCLUDE
#define statesplashscreen_INCLUDE

#include "Game.h"
#include "Bitmap.h"

//StateSplashScreen inherits GameState class
class StateSplashScreen :public GameState{
public:
	StateSplashScreen(); //constructor
	virtual ~StateSplashScreen(); //deconstructor

	virtual void init();
	virtual void draw(SDL_Window * window); //draw the game state 
	virtual void handleEvent(SDL_Event const &sdlEvent, Game &context); //method to handle what state the game is at
	virtual void update(Game &context); //update the gamestate
	virtual void Cleanup(); //delete everything that is unused so that memory can be freed
	void displayMenuText(); //method to draw the menu text on the menu state
	virtual void enter();

private:
	//pointers for the text displayed on the splash screen
	Label* loadLabel;

	//pointers for bitmap images to be displayed on splash screen
	Bitmap *companyLogo;

	TTF_Font* textFont;	// SDL type for True-Type font rendering

	int timeOfEnteredState;



};

#endif