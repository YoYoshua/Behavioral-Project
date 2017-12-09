#include "Game.h"

using namespace sf;

int main()
{
	Game game;

	game.initialiseVariables();

	while (game.gameWindow.isOpen())
	{
		game.handleInput();
		game.updateScene();
		game.drawScene();
	}
	return 0;
}