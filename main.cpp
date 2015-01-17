// Game Engine Design - SDL base code
// This sample project has a complete lack of OO design and makes use of
// a very large number of global variables. What it does do, is demonstrate
// use of SDL for window/event management with OpenGL for graphics rendering
// This project requires the following 3rd party libraries:
// - glew (GL extension wrangler, for access to OpenGL past 1.1 on Windows)
// - SDL (base libraries)
// - SDL_ttf (to render text to a surface/texture for display in OpenGL)
//
// There are MANY ways to improve this code, some of which are identified in
// comments, and these are left as an exercise to the reader
// 
// Copyright (C) 2012 Daniel Livingstone
//
// This software is provided 'as-is', without any express or implied
// warranty.  In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.


// Thanks to Cristi Szabo for fixes to label rendering to resolve issues with
// some versions of OpenGL drivers/hardware


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
