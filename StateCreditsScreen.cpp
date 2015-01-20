#include "StateCreditsScreen.h"


StateCreditsScreen::StateCreditsScreen() //constructor
{
	//Initiatlising NULL pointers so that we dont accidently delete them
	titleLabel = nullptr;
	nameLabel = nullptr;
}
StateCreditsScreen:: ~StateCreditsScreen() //deconstructor
{
	//if memory has been allocated already then free it up
	if (titleLabel != 0)
		delete titleLabel;
	if (nameLabel != 0)
		delete nameLabel;

}

void StateCreditsScreen::init()
{
	textFont = TTF_OpenFont("MavenPro-Regular.ttf", 24);

	SDL_Color displayColor = { 255, 255, 0 }; //displaycolor

	titleLabel = new Label();
	nameLabel = new Label();

	yOffset = 0;

	titleLabel->textToTexture("Programmer", textFont, displayColor);
	nameLabel->textToTexture("Victoria Russell", textFont, displayColor);
}

void StateCreditsScreen::draw(SDL_Window * window, Game &context) //draw the game state 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear window

	//starting point for the title
	titleLabel->draw(450,0 + yOffset);
	//starting point for name
	nameLabel->draw(450, -50 + yOffset);

	SDL_GL_SwapWindow(window); // swap buffers

}
void StateCreditsScreen:: handleEvent(SDL_Event const &sdlEvent, Game &context) //method to handle what state the game is at
{

}

//update the gamestate
void StateCreditsScreen::update(Game &context){
	yOffset += 1; //creating the scrolling credits effect

	if (yOffset >= 1024)
		context.setState(context.getMainMenuState());

} 
void StateCreditsScreen::Cleanup(){} //delete everything that is unused so that memory can be freed

void StateCreditsScreen::enter(Game &context)
{
	yOffset = 0; //resetting the yOffset
}