#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "snake.h"
#include "player.h"
#include "cpuSnake.h"
#include <vector>
#include <time.h>

class Game
{
private:

	const int newSnakeHeadSize{ 10 };

	std::vector <Food> allFood;
	std::vector <Snake*> allPlayers;
	int foodSpawnRate{ 3 };
	int waterDropRate{ 3 };
	
	bool allFoodPresent{ false };
	int playerNumber = 1;
	
	sf::Font font;
	sf::Color newSnakeColor;
	
	
	const int screenWidth{ 800 };
	const int screenHeight{ 600 };
	const int gameDelay{ 300 };
	const int &h = newSnakeHeadSize * 2;
public:

	
	void PlayGame(sf::RenderWindow & window, const int &numberOfPlayers, const int &numberOfcpuPlayers, const sf::Sprite &background);
	void DisplayText(sf::RenderWindow & window, Snake* player);
	void displayGameOver(sf::RenderWindow & window);
	void generateFood(const int &screenWidth, const int &screenHeight, const int &snakeHeadSize);
	void renderWalls(sf::RenderWindow & window);
	
	
};