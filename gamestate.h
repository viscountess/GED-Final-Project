#ifndef gamestate_INCLUDE
#define gamestate_INCLUDE
#include <SDL.h>
class Game; // Forward declaration of Game class 

//Abstract base class for the gamestates
class GameState{
public:
	
	virtual ~GameState() {} //de-constructor
	virtual void init() = 0;
	virtual void draw(SDL_Window * window) = 0; //draw the game state 
	virtual void handleEvent(SDL_Event const &sdlEvent, Game &context) = 0; //method to handle what state the game is at
	virtual void update(Game &context) = 0; //update the gamestate
	virtual void Cleanup() = 0; //delete everything that is unused so that memory can be freed
	virtual void enter() = 0;

};

#endif //gamestate_INCLUDE