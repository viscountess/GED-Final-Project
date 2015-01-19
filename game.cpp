#include "game.h"
#include "StateMainMenu.h"
#include "StatePlay.h"
#include "StateCreditsScreen.h"
#include "StateSplashScreen.h"
#include "StateCharacterScreen.h"
#include "StateBattle.h"


//Window size - windowW = width, windowH = height
int windowW = 1024;
int windowH = 1024;

// We should be able to detect when errors occur with SDL if there are 
// unrecoverable errors, then we need to print an error message and quit the program
void Game::exitFatalError(char *message)
{
	std::cout << message << " " << SDL_GetError();
	SDL_Quit();
	exit(1);
}


// Set up rendering context
// Sets values for, and creates an OpenGL context for use with SDL
SDL_Window * Game::setupRC(SDL_GLContext &context)
{
	SDL_Window *window;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) // Initialize video
		exitFatalError("Unable to initialize SDL");

	// Request an OpenGL 2.1 context.
	// If you request a context not supported by your drivers, no OpenGL context will be created
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);  // double buffering on
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8); // 8 bit alpha buffering

	// Optional: Turn on x4 multisampling anti-aliasing (MSAA)
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

	// Create 800x600 window
	window = SDL_CreateWindow("GED Final Project",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		windowW, windowH, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (!window) // Check window was created OK
		exitFatalError("Unable to create window");

	context = SDL_GL_CreateContext(window); // Create opengl context and attach to window
	SDL_GL_SetSwapInterval(1); // set swap buffers to sync with monitor's vertical refresh rate

	// set up TrueType / SDL_ttf
	if (TTF_Init() == -1)
		exitFatalError("TTF failed to initialise.");
	return window;
}


// Initialise OpenGL values and game related values and variables
void Game::glInit(void)
{    
	glViewport(0, 0, windowW, windowH);
	gluOrtho2D(0, windowW, 0, windowH);
	glMatrixMode(GL_PROJECTION);			//Use projection mode
	glLoadIdentity();						//Reset view  
}


// The main rendering function
// In principle, this function should never perform updates to the game
// ONLY render the current state. Reacting to events should be taken care
// of in a seperate update function
void Game::draw(SDL_Window *window)
{
	
}


// The event handling function
// In principle, this function should never perform updates to the game
// ONLY detect what events have taken place. Reacting to the events should 
// be taken care of in a seperate update function
// This would allow e.g. diagonal movement when two keys are pressed together
// (which is not possible with this implementation)
void Game::handleSDLEvent(SDL_Event const &sdlEvent)
{
	
}

//constructor
Game::Game(){
	
}

//deconstructor
Game::~Game(){
	
	SDL_DestroyWindow(window);
	SDL_Quit();
	
}

void Game::init(){
	SDL_GLContext glContext; // OpenGL context handle
	window = setupRC(glContext); // Create window and render context
	glInit(); // initialise the OpenGL and game variables
	

	//testing to see if the state manager works
	playState = new StatePlay();
	mainMenuState = new StateMainMenu();
	creditsState = new StateCreditsScreen();
	splashState = new StateSplashScreen();
	characterState = new StateCharacterScreen();
	battleState = new StateBattle();
	currentState = splashState;

	playState->init();
	creditsState->init();
	mainMenuState->init();
	splashState->init();
	characterState->init();
	battleState->init();

	monster = new MonsterManager();
	monster->init();
}

void Game::gameQuit(){

	running = false;
}

void Game::run(){
	running = true;
	SDL_Event sdlEvent; // variable to detect SDL events

	std::cout << "Progress: About to enter main loop" << std::endl;

	// unlike GLUT, SDL requires you to write your own event loop
	// This puts much more power in the hands of the programmer
	// This simple loop only responds to the window being closed.
	while (running)	// the event loop
	{
		while (SDL_PollEvent(&sdlEvent))
		{
			if (sdlEvent.type == SDL_QUIT)
				running = false;
			else
				currentState->handleEvent(sdlEvent, *this);
		}
		currentState->update(*this); //calling the update function
		currentState->draw(window, *this); //draw the current state to the screen

	}
}

void Game::setState(GameState * newState){
	if (newState != currentState)
	{
		
		currentState = newState;
		currentState->enter();
		
	}

}

//returns getState to the currentState pointer
GameState *Game::getState(void){
	return currentState;
}

//returns getPlayState to the playState pointer
GameState *Game::getPlayState(void){
	return playState;
}

//returns getMainMenuState to the mainMenuState pointer
GameState *Game::getMainMenuState(void){
	return mainMenuState;
}

//returns getCreditsState to the creditsState pointer
GameState *Game::getCreditsState(void){
	return creditsState;
}

GameState *Game::getCharacterState(void){
	return characterState;
}

GameState *Game::getBattleState(void){
	return battleState;
}