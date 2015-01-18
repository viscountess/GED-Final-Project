#ifndef game_INCLUDE
#define game_INCLUDE

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_opengl.h>

// C stdlib and C time libraries for rand and time functions
#include <cstdlib>
#include <ctime>
// iostream for cin and cout
#include <iostream>
// stringstream and string
#include <sstream>
#include <string>

#include "label.h"
#include "gamestate.h"

class Game{
public:
	Game();//constructor
	~Game();//deconstructor

	void init();
	void run();

	void setState(GameState * newState);
	GameState *getState(void); //returns getState to the currentState pointer
	GameState *getPlayState(void); //returns getPlayState to the playState pointer
	GameState *getCreditsState(void); //returns getCreditsState to the creditsState pointer
	GameState *getMainMenuState(void); //returns getMainMenuState to the mainMenuState pointer
	GameState *getCharacterState(void); //returns getCharacterState to the characterState pointer
	void gameQuit(); //function to set running to false so that the game quits

private:
	
	//declaring window pointer a member variable
	SDL_Window *window;

	void exitFatalError(char *message);
	SDL_Window * setupRC(SDL_GLContext &context);
	void glInit(void);
	
	void draw(SDL_Window *window);
	void handleSDLEvent(SDL_Event const &sdlEvent);

	//data member pointer variables for the gamestates
	GameState* currentState;
	GameState* playState;
	GameState* mainMenuState;
	GameState* creditsState;
	GameState* splashState;
	GameState* characterState;

	bool running; // set running to true

};


#endif //game_INCLUDE

