#include "StateGameOver.h"

//constructor
StateGameOver::StateGameOver(){

	//Initiatlising NULL pointers so that we dont accidently delete them
	gameOverLabel = nullptr;
}

//deconstructor
StateGameOver::~StateGameOver(){

	//if memory has been allocated already then free it up
	if (gameOverLabel != 0)
		delete gameOverLabel;
}

void StateGameOver::init(){

	textFont = TTF_OpenFont("MavenPro-Regular.ttf", 24);

	SDL_Color displayColor = { 255, 255, 0 }; //displaycolor

	gameOverLabel = new Label();

	gameOverLabel->textToTexture("GAME OVER", textFont, displayColor);

}
void StateGameOver::draw(SDL_Window * window, Game &context) //draw the game state 
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear window

	//starting point for the title
	gameOverLabel->draw(512 - (gameOverLabel->getWidth() / 2), 450);


	SDL_GL_SwapWindow(window); // swap buffers

}
void StateGameOver::handleEvent(SDL_Event const &sdlEvent, Game &context) //method to handle what state the game is at
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
void StateGameOver::update(Game &context) //update the gamestate
{

}
void StateGameOver::Cleanup() //delete everything that is unused so that memory can be freed
{

}
void StateGameOver::enter(Game &context)
{

}