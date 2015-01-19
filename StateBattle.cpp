#include "StateBattle.h"

void StateBattle::init(){}
void StateBattle::draw(SDL_Window * window, Game &context) //draw the game state 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear window
	SDL_Color colour = { 255, 255, 0 };

	context.getMonsterManager()->getBattleMonster()->renderAt(124,512);
	context.getMonsterManager()->getPlayer()->renderAt(900,512);

	SDL_GL_SwapWindow(window); // swap buffers
}
void StateBattle::handleEvent(SDL_Event const &sdlEvent, Game &context){} //method to handle what state the game is at
void StateBattle::update(Game &context){} //update the gamestate
void StateBattle::Cleanup(){} //delete everything that is unused so that memory can be freed