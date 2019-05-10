#pragma once
#include <SFML/Graphics.hpp>

class Water
{
private:

	sf::Vector2f position{ 0,100 };
	sf::Vector2f size;
	sf::Color color{ 0,0,255,100 };
	
public:

	Water(const int& screenHeight, const int& screenWidth);
	~Water();
	void render(sf::RenderWindow & window);
	void sink(const int &snakeHeadSize);
	sf::Vector2f getPosition();
	sf::Vector2f getSize();

};