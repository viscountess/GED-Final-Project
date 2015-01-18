#include "StatePlay.h"

//constructor
StatePlay::StatePlay(){

	
	xpos = 0.0f;
	ypos = 0.0f;
	xsize = 0.15f;
	ysize = 0.15f;

	targetXPos = 0.0f;
	targetYPos = 0.0f;
	targetXSize = 0.1f;
	targetYSize = 0.1f;

	score = 0;


} 

//deconstructor
StatePlay:: ~StatePlay(){
	delete playerLabel;
	delete targetLabel;

	TTF_CloseFont(textFont);
}

void StatePlay::init(){

	textFont = TTF_OpenFont("MavenPro-Regular.ttf", 24);
	//if (textFont == NULL)
	//	exitFatalError("Failed to open font."); 

	//initialise new label objects
	playerLabel = new Label();
	targetLabel = new Label();

	SDL_Color colour = { 255, 255, 0 };
	//create textures from strings
	playerLabel->textToTexture("player", textFont, colour);
	targetLabel->textToTexture("target", textFont, colour);

	// Initialise OpenGL values and game related values and variables
	glClearColor(0.0, 0.0, 0.0, 0.0); // set background colour

	std::srand(std::time(NULL));
	targetXPos = (float)rand() / RAND_MAX - 0.75f;
	targetYPos = (float)rand() / RAND_MAX - 0.75f;
	lastTime = clock();
	//
}

//draw the game state
void StatePlay::draw(SDL_Window * window){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear window

	// draw player
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(xpos, ypos, 0.0); // first corner
	glVertex3f(xpos + xsize, ypos, 0.0); // second corner
	glVertex3f(xpos + xsize, ypos + ysize, 0.0); // third corner
	glVertex3f(xpos, ypos + ysize, 0.0); // fourth corner
	glEnd();
	//displayString(xpos + (xsize / 2.0f), ypos + ysize, playerLabel, playerWidth, playerHeight);
	playerLabel->draw(xpos + (xsize / 2.0f), ypos + ysize);

	// draw target
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(targetXPos, targetYPos, 0.0); // first corner
	glVertex3f(targetXPos + targetXSize, targetYPos, 0.0); // second corner
	glVertex3f(targetXPos + targetXSize, targetYPos + targetYSize, 0.0); // third corner
	glVertex3f(targetXPos, targetYPos + targetYSize, 0.0); // fourth corner
	glEnd();
	//displayString(targetXPos + (targetXSize / 2.0f), targetYPos + targetYSize, targetLabel, targetWidth, targetHeight);
	targetLabel->draw(targetXPos + (targetXSize / 2.0f), targetYPos + targetYSize);

	if ((targetXPos >= xpos) && (targetXPos + targetXSize <= xpos + xsize)	// cursor surrounds target in x
		&& (targetYPos >= ypos) && (targetYPos + targetYSize <= ypos + ysize)) // cursor surrounds target in y
	{
		score += 100; // congrats, player has scored!
		// randomize the new target position
		targetXPos = (float)rand() / RAND_MAX - 0.75f;
		targetYPos = (float)rand() / RAND_MAX - 0.75f;
	}

	// Calculate ms/frame
	// Some OpenGL drivers will limit the frames to 60fps (16.66 ms/frame)
	// If so, expect to see the time to rapidly switch between 16 and 17...
	glColor3f(1.0, 1.0, 1.0);
	currentTime = clock();
	// On some systems, CLOCKS_PER_SECOND is 1000, which makes the arithmetic below redundant
	// - but this is not necessarily the case on all systems
	float milliSecondsPerFrame = ((currentTime - lastTime) / (float)CLOCKS_PER_SEC * 1000);

	// Print out the score and frame time information
	std::stringstream strStream;
	strStream << "Score:" << score;
	strStream << "          ms/frame: " << milliSecondsPerFrame;

	SDL_Color colour = { 255, 255, 0 };
	//Creating new timer label
	Label* timerLabel = new Label();
	timerLabel->textToTexture(strStream.str().c_str(), textFont, colour);
	timerLabel->draw(-0.9, 0.9);
	delete timerLabel;
	lastTime = clock();

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
			ypos += 0.05f;
			break;
		case SDLK_DOWN:
		case 's': case 'S':
			ypos -= 0.05f;
			break;
		case SDLK_LEFT:
		case 'a': case 'A':
			xpos -= 0.05f;
			break;
		case SDLK_RIGHT:
		case 'd': case 'D':
			xpos += 0.05f;
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
