#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <Game.hpp>


int main() {

	mt::Game game;
	game.Setup	(900, 504, "Flappy Bird");
	game.Run	(900, 504);

	return 0;
}