#pragma once
#include "game.hpp"

void startGame()
{
	Game game;
	game.initWorld();
	game.newGame();
	game.gameLoop();
}

void loadGame(std::string fileName)
{
}	
