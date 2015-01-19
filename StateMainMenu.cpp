#include "StateMainMenu.h"

//constructor
StateMainMenu::StateMainMenu(){

	//Initiatlising NULL pointers so that we dont accidently delete them
	playLabel = nullptr;
	creditLabel = nullptr;
	quitLabel = nullptr;
}

//deconstructor
StateMainMenu:: ~StateMainMenu(){

}

void StateMainMenu::init(){

	textFont = TTF_OpenFont("MavenPro-Regular.ttf", 24);
	//if (textFont == NULL)
	//	exitFatalError("Failed to open font."); 


	//Green means label is selected
	//red means label is unselected
	SDL_Color selectColor = { 0, 255, 0 };
	SDL_Color deselectColor = { 255, 0, 0 };
	setupLabels(selectColor, deselectColor, deselectColor);
	
	currentSelection = playLabel;
}

//function to quickly change the colour of the menu buttons
void StateMainMenu::setupLabels(SDL_Color playColor, SDL_Color creditsColor, SDL_Color quitColor ){

	//If the memory has been allocated already, then free it up
	//for the new label.
	if (playLabel != 0)
		delete playLabel;
	if (quitLabel != 0)
		delete quitLabel;
	if (creditLabel != 0)
		delete creditLabel;
	//

	//initialise new label objects
	playLabel = new Label();
	quitLabel = new Label();
	creditLabel = new Label();

	//create textures from strings
	playLabel->textToTexture("Play", textFont, playColor);
	creditLabel->textToTexture("Credits", textFont, creditsColor);
	quitLabel->textToTexture("Quit", textFont, quitColor);
}

//draw the game state
void StateMainMenu::draw(SDL_Window * window, Game &context){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear window

	//starting point for the Play button
	playLabel->draw(512-(playLabel->getWidth()/2), 512);
	//starting point for the credits screen
	creditLabel->draw(512-(creditLabel->getWidth()/2), 412);
	//starting point for the quit button
	quitLabel->draw(512-(quitLabel->getWidth()/2), 312);

	SDL_GL_SwapWindow(window); // swap buffers
}



//method to draw the menu text on the menu state
void StateMainMenu::displayMenuText(){

}

//function to manage what happens if player presses up on the keyboard
void StateMainMenu::handleUPpress(){

	SDL_Color selectColor = { 0, 255, 0 };
	SDL_Color deselectColor = { 255, 0, 0 };

	
	// if the play button is selected
	if (currentSelection == playLabel)
	{
		//then if press up - do this
		setupLabels(deselectColor, deselectColor, selectColor);
		currentSelection = quitLabel;
	}
	//if the credit button is selected
	else if (currentSelection == creditLabel)
	{
		//if press up - then highlight the play button
		setupLabels(selectColor, deselectColor, deselectColor);
		currentSelection = playLabel;
	}
	//if quit button is selected
	else if (currentSelection == quitLabel)
	{
		//if press up then highlight the credit button
		setupLabels(deselectColor, selectColor, deselectColor);
		currentSelection = creditLabel;
	}
}

//function to manage what happens when player presses down on the keyboard
void StateMainMenu::handleDOWNpress(){

	SDL_Color selectColor = { 0, 255, 0 };
	SDL_Color deselectColor = { 255, 0, 0 };

	// if the play button is selected
	if (currentSelection == playLabel)
	{
		//then if press down then highlight the credit button
		setupLabels(deselectColor, selectColor, deselectColor);
		currentSelection = creditLabel;
	}
	//if the credit button is selected
	else if (currentSelection == creditLabel)
	{
		//if press down - then highlight the quit button
		setupLabels(deselectColor, deselectColor, selectColor);
		currentSelection = quitLabel;
	}
	//if quit button is selected
	else if (currentSelection == quitLabel)
	{
		//if press down then highlight the play button
		setupLabels(selectColor, deselectColor, deselectColor);
		currentSelection = playLabel;
	}
}

//function to handle what happens when enter is pressed
//depending on what button is highlighted
void StateMainMenu::handleENTERpress(Game &context){

	if (currentSelection == playLabel)
		context.setState(context.getCharacterState());
	else if (currentSelection == creditLabel)
		context.setState(context.getCreditsState());
	else if (currentSelection == quitLabel)
		context.gameQuit();
}


//method to handle what state the game is at
void StateMainMenu::handleEvent(SDL_Event const &sdlEvent, Game &context){

	//if the player clicks anywhere on the screen (for now)
	//Then go to play state
	if (sdlEvent.type == SDL_KEYDOWN)
	{
		
		switch (sdlEvent.key.keysym.sym)
		{
		case SDLK_UP:
			handleUPpress();
			break;
		case SDLK_DOWN:
			handleDOWNpress();
			break;
		case SDLK_RETURN:
			handleENTERpress(context);
			break;
		default:
			break;
		}
		
	}
		
}

//update the gamestate
void StateMainMenu::update(Game &context){

}

//delete everything that is unused so that memory can be freed
void StateMainMenu::Cleanup(){

}