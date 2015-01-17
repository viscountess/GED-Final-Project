


#include "game.h"

// SDL projects do not automatically work with the console window. 
// On windows with visual studio, the following line is required to use console output
#if _DEBUG
#pragma comment(linker, "/subsystem:\"console\" /entry:\"WinMainCRTStartup\"")
#endif

// Program entry point
// SDL manages the actual WinMain entry point for us
int main(int argc, char *argv[])
{
    
	Game* mygame=new Game();
	mygame->init();
	mygame->run();
	
	delete mygame;
    return 0;
}
