#include "StateGameWin.h"

//constructor
StateGameWin::StateGameWin(){

	//Initiatlising NULL pointers so that we dont accidently delete them
	gameWinLabel = nullptr;
}

//deconstructor
StateGameWin::~StateGameWin(){

	//if memory has been allocated already then free it up
	if (gameWinLabel != 0)
		delete gameWinLabel;
}

void StateGameWin::init(){

	textFont = TTF_OpenFont("MavenPro-Regular.ttf", 24);

	SDL_Color displayColor = { 255, 255, 0 }; //displaycolor

	gameWinLabel = new Label();

	gameWinLabel->textToTexture("CONGRATS - YOU WON!!", textFont, displayColor);

}
void StateGameWin::draw(SDL_Window * window, Game &context) //draw the game state 
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear window

	//starting point for the title
	gameWinLabel->draw(512 - (gameWinLabel->getWidth() / 2), 450);


	SDL_GL_SwapWindow(window); // swap buffers

}
void StateGameWin::handleEvent(SDL_Event const &sdlEvent, Game &context) //method to handle what state the game is at
{
	if (sdlEvent.type == SDL_KEYDOWN)
	{

		switch (sdlEvent.key.keysym.sym)
		{
			//If either return or space is pressed during game over screen 
			//then go to the main menu
		case SDLK_RETURN:
		case SDLK_SPACE:
			context.setState(context.getMainMenuState());
			break;
			//If any other keys is pressed then do nothing
		default:
			break;
		}

	}
}
void StateGameWin::update(Game &context) //update the gamestate
{

}
void StateGameWin::Cleanup() //delete everything that is unused so that memory can be freed
{

}
void StateGameWin::enter(Game &context)
{

}