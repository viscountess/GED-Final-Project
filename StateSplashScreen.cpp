#include "StateSplashScreen.h"
#include "Bitmap.h"

StateSplashScreen::StateSplashScreen() //constructor
{
	//Initiatlising NULL pointers so that we dont accidently delete them
	loadLabel = nullptr;

	timeOfEnteredState = 0;

	companyLogo = new Bitmap("images/game studio logo.bmp", false);

}
StateSplashScreen:: ~StateSplashScreen() //deconstructor
{
	//if memory has been allocated already then free it up
	if (loadLabel != 0)
		delete loadLabel;
}

void StateSplashScreen::init()
{
	textFont = TTF_OpenFont("MavenPro-Regular.ttf", 24);

	SDL_Color displayColor = { 255, 255, 0 }; //displaycolor

	loadLabel = new Label();

	loadLabel->textToTexture("LOADING", textFont, displayColor);
}

void StateSplashScreen::draw(SDL_Window * window) //draw the game state 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear window

	
	companyLogo->drawAt(0,600);

	//starting point for the title
	loadLabel->draw(512-(loadLabel->getWidth()/2), 450);
	

	SDL_GL_SwapWindow(window); // swap buffers
}

void StateSplashScreen::handleEvent(SDL_Event const &sdlEvent, Game &context) //method to handle what state the game is at
{
	if (sdlEvent.type == SDL_KEYDOWN)
	{

		switch (sdlEvent.key.keysym.sym)
		{
			//If either return or space is pressed during loading screen 
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

void StateSplashScreen::update(Game &context) //update the gamestate
{
	//When splash screen timer reaches 3 seconds

	if ((SDL_GetTicks() - timeOfEnteredState) > 3000)
		context.setState(context.getMainMenuState());
}


void StateSplashScreen::Cleanup() //delete everything that is unused so that memory can be freed
{}

void StateSplashScreen::displayMenuText()
{}

void StateSplashScreen:: enter()
{
	timeOfEnteredState = SDL_GetTicks();

}