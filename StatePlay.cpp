#include "StatePlay.h"
#include "Champion.h"
#include "MonsterNPC.h"
#include "Brute.h"
#include "Fodder.h"
#include "Raider.h"
#include "Shaman.h"

//constructor
StatePlay::StatePlay(){

} 

//deconstructor
StatePlay:: ~StatePlay(){
	
	TTF_CloseFont(textFont);
}

void StatePlay::init(){

	textFont = TTF_OpenFont("MavenPro-Regular.ttf", 24);
	//if (textFont == NULL)
	//	exitFatalError("Failed to open font."); 

	SDL_Color colour = { 255, 255, 0 };

	// Initialise OpenGL values and game related values and variables
	glClearColor(0.0, 0.0, 0.0, 0.0); // set background colour

	lastTime = clock();


}

//draw the game state
void StatePlay::draw(SDL_Window * window, Game &context){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear window

	//render the monsters onscreen
	for (int i = 0; i < 3; i++)
	{
		context.getMonsterManager()->getMonster(i)->render();
	}

	//render the player onscreen
		context.getMonsterManager()->getPlayer()->render();
	

	// Calculate ms/frame
	// Some OpenGL drivers will limit the frames to 60fps (16.66 ms/frame)
	// If so, expect to see the time to rapidly switch between 16 and 17...
	glColor3f(1.0, 1.0, 1.0);
	currentTime = clock();
	// On some systems, CLOCKS_PER_SECOND is 1000, which makes the arithmetic below redundant
	// - but this is not necessarily the case on all systems
	float milliSecondsPerFrame = ((currentTime - lastTime) / (float)CLOCKS_PER_SEC * 1000);

	SDL_Color colour = { 255, 255, 0 };
	

	SDL_GL_SwapWindow(window); // swap buffers
}

//method to handle what state the game is at
void StatePlay::handleEvent(SDL_Event const &sdlEvent, Game &context){
	if (sdlEvent.type == SDL_KEYDOWN)
	{
		//std::cout << "Scancode: " << sdlEvent.key.keysym.scancode  ;
		//std::cout <<  ", Name: " << SDL_GetKeyName( sdlEvent.key.keysym.sym ) << std::endl;
		switch (sdlEvent.key.keysym.sym)
		{
		case SDLK_UP:
		case 'w': case 'W':
			context.getMonsterManager()->getPlayer()->adjustYPos(5);
			break;
		case SDLK_DOWN:
		case 's': case 'S':
			context.getMonsterManager()->getPlayer()->adjustYPos(-5);
			break;
		case SDLK_LEFT:
		case 'a': case 'A':
			context.getMonsterManager()->getPlayer()->adjustXPos(-5);
			break;
		case SDLK_RIGHT:
		case 'd': case 'D':
			context.getMonsterManager()->getPlayer()->adjustXPos(5);
			break;
		case SDLK_ESCAPE:
			context.setState(context.getMainMenuState());
			break;
		default:
			break;
		}
	}
}

//update the gamestate
void StatePlay::update(Game &context){
	for (int i = 0; i < 3; i++)
	{
		//Collision detection
		float x = context.getMonsterManager()->getMonster(i)->getXPos() - context.getMonsterManager()->getPlayer()->getXPos();
		float y = context.getMonsterManager()->getMonster(i)->getYPos() - context.getMonsterManager()->getPlayer()->getYPos();
		float distToPlayer = sqrt((x*x) + (y*y));

		if (distToPlayer <= 50)
		{
			context.getMonsterManager()->setBattleMonsterIndex(i);
			context.setState(context.getBattleState());
		}
	}
}

//delete everything that is unused so that memory can be freed
void StatePlay::Cleanup(){

}