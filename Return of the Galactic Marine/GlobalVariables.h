#ifndef GLOBAL_VARIABLES
#define GLOBAL_VARIABLES

#include "Game.h"

namespace Global
{
	extern Game		*currentGame;
	extern Player	*currentPlayer;
	extern int screenX;
	extern int screenY;
	extern bool newGameStarted;
	extern TTF_Font* textFont;		// SDL type for True-Type font rendering
}

#endif