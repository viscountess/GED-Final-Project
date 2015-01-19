#include "StatePlay.h"
#include "Champion.h"
#include "MonsterNPC.h"

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

	monster = new Champion(new MonsterNPC("Champion"));
	//
}

//draw the game state
void StatePlay::draw(SDL_Window * window){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear window

	monster->render();

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
			
			break;
		case SDLK_DOWN:
		case 's': case 'S':
		
			break;
		case SDLK_LEFT:
		case 'a': case 'A':
		
			break;
		case SDLK_RIGHT:
		case 'd': case 'D':
			
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

}

//delete everything that is unused so that memory can be freed
void StatePlay::Cleanup(){

}