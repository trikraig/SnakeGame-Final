#include "food.h"

Food::Food(sf::Vector2f new_position, sf::Color new_color, int new_score) : position(new_position), color(new_color), score(new_score)
{
	loadFoodTextures();
}

void Food::loadFoodTextures()
{
	if (!food1.loadFromFile("food1.png"))
	{
		//Create error.
	}
	if (!food2.loadFromFile("food2.png"))
	{
		//Create error.
	}
	if (!food3.loadFromFile("food3.png"))
	{
		//Create error.
	}
	if (!food4.loadFromFile("food4.png"))
	{
		//Create error.
	}
	if (!food5.loadFromFile("food5.png"))
	{
		//Create error.
	}
}

void Food::applySprites()
{
	switch (score)
	{
	case 1:
		currentSprite.setTexture(food1);
		break;
	case 2:
		currentSprite.setTexture(food2);
		break;
	case 3:
		currentSprite.setTexture(food3);
		break;
	case 4:
		currentSprite.setTexture(food4);
		break;
	case 5:
		currentSprite.setTexture(food5);
		break;

	}
}

void Food::Render(sf::RenderWindow & window, const int &snakeHeadSize)
{
	applySprites();

	if (isAlive == true)
	{
		currentSprite.setScale(1.5, 1.5);
		currentSprite.setPosition(position.x, position.y);

		//Previously used a circle in different colours to represent food and score.
		/*
		sf::CircleShape *shape = new sf::CircleShape((float)snakeHeadSize);
		shape->setFillColor(color);
		shape->setPosition(position.x , position.y);

		window.draw(*shape);
		delete shape;*/

		window.draw(currentSprite);
	}

}

int Food::getScore()
{
	return score;
}

sf::Vector2f Food::getPosition()
{
	return position;
}

void Food::generateNewValues(const int &screenWidth, const int &screenHeight, const int &snakeHeadSize)
{
	int xPos, yPos;
	const int &h = snakeHeadSize * 2;

	//Generates new random position and alligns to grid by using int's ability to round up 
	xPos = rand() % ((int)screenWidth + 10);
	xPos = (xPos / h) * h;
	yPos = rand() % (int)screenHeight + 10;
	yPos = (yPos / h) * h;

	sf::Vector2f newPosition{ (float)xPos , (float)yPos };

	position = newPosition;

	score = (rand() % 4) + 1;

	//No longer used now food is using sprites.
	/*switch (score)
	{
	case 1:
		color = sf::Color{ 128, 255 , 0, 255 };
		break;
	case 2:
		color = sf::Color{ 255, 255 , 0, 255 };
		break;
	case 3:
		color = sf::Color{ 255, 128 , 0, 255 };
		break;
	case 4:
		color = sf::Color{ 255, 0 , 0, 255 };
		break;
	case 5:
		color = sf::Color{ 255, 255 , 255, 255 };
		break;

	default:
		break;
	}*/

}

void Food::toggleAlive()
{
	isAlive = !isAlive;
}

bool Food::getState()
{
	return isAlive;
}


void Food::floatDown(const sf::Vector2f &waterPos)
{
	//Lowers food relative to the water position.
	if (position.y < waterPos.y)
	{
		position.y = waterPos.y;
	}

}
