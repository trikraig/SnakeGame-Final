#pragma once
#include <SFML/Graphics.hpp>

class Food
{
private:

	sf::Vector2f position;
	sf::Color color;
	sf::Texture food1;
	sf::Texture food2;
	sf::Texture food3;
	sf::Texture food4;
	sf::Texture food5;
	sf::Sprite currentSprite;
	int score;
	bool isAlive{ false };

public:

	Food(sf::Vector2f new_position, sf::Color new_color, int new_score);

	void loadFoodTextures();
	void applySprites();
	void Render(sf::RenderWindow & window, const int &snakeHeadSize);
	void generateNewValues(const int &screenWidth, const int &screenHeight, const int &snakeHeadSize);
	void toggleAlive();
	void floatDown(const sf::Vector2f &waterPos);
	int getScore();
	bool getState();
	sf::Vector2f getPosition();

};