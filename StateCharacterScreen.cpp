#include"StateCharacterScreen.h"


StateCharacterScreen::StateCharacterScreen() //constructor
{
	//Initiatlising NULL pointers so that we dont accidently delete them
	championLabel = nullptr;
	shamanLabel = nullptr;
}
StateCharacterScreen:: ~StateCharacterScreen() //deconstructor
{
	//if memory has been allocated already then free it up
	if (championLabel != 0)
		delete championLabel;
	if (shamanLabel != 0)
		delete shamanLabel;
}

void StateCharacterScreen::init()
{
	textFont = TTF_OpenFont("MavenPro-Regular.ttf", 24);

	SDL_Color displayColor = { 255, 255, 0 }; //displaycolor

	championLabel = new Label();
	shamanLabel = new Label();

	championLabel->textToTexture("Champion", textFont, displayColor);
	shamanLabel->textToTexture("Shaman", textFont, displayColor);
}

void StateCharacterScreen::draw(SDL_Window * window, Game &context) //draw the game state 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear window

	//starting point for labels
	championLabel->draw(256, 512);
	shamanLabel->draw(768, 512);


	SDL_GL_SwapWindow(window); // swap buffers
}

void StateCharacterScreen::handleEvent(SDL_Event const &sdlEvent, Game &context) //method to handle what state the game is at
{
	if (sdlEvent.type == SDL_KEYDOWN)
	{

		switch (sdlEvent.key.keysym.sym)
		{
			//If space is pressed during character select screen 
			//then go to the play state
		case SDLK_RETURN:
			context.setState(context.getPlayState());
			break;
			//if backspace is pressed then go back to the main menu
		case SDLK_BACKSPACE:
			context.setState(context.getMainMenuState());
			break;
			//If any other keys is pressed then do nothing
		default:
			break;
		}

	}
}

void StateCharacterScreen::update(Game &context) //update the gamestate
{

}


void StateCharacterScreen::Cleanup() //delete everything that is unused so that memory can be freed
{}

void StateCharacterScreen::displayMenuText()
{}

void StateCharacterScreen::enter(Game &context)
{

}