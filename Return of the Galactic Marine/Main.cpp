// Game Engine Design - SDL base code, OO version 1
// This sample project makes limited use of OO design, and demonstrates
// use of SDL for window/event management with OpenGL for graphics rendering
// This project requires the following 3rd party libraries:
// - glew (GL extension wrangler, for access to OpenGL past 1.1 on Windows)
// - SDL (base libraries)
// - SDL_ttf (to render text to a surface/texture for display in OpenGL)
//
// There remain MANY ways to improve this code, some of which are identified in
// comments, and these are left as an exercise to the reader
//
// Copyright (C) 2012 Daniel Livingstone
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
// claim that you wrote the original software. If you use this software
// in a product, an acknowledgment in the product documentation would be
// appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
// misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#include <iostream>
#include "Game.h"

#if _DEBUG
#pragma comment(linker, "/subsystem:\"console\" /entry:\"WinMainCRTStartup\"")
#endif

int main(int argc, char *argv[])
{
   // SDL_GLContext glContext; // OpenGL context handle
	Game *newGame = new Game();

    //SDL_Window *window = setupRC(glContext); // Create window and render context
	newGame->init(); // initialise the OpenGL and game variables
	newGame->run();

	delete newGame;
    return 0;
}