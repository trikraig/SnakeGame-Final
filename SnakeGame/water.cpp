#include "water.h"



Water::Water(const int & screenHeight, const int & screenWidth)
{
	size.x = (float) screenWidth;
	size.y = (float) screenHeight;
	
}

Water::~Water()
{
}

void Water::render(sf::RenderWindow & window)
{
	
	sf::RectangleShape rectangle(sf::Vector2f(120, 50)); //Offset position from top of screen.
	
	rectangle.setPosition(position);
	rectangle.setFillColor(color);
	rectangle.setSize(size);

	window.draw(rectangle);

	

}

void Water::sink(const int &snakeHeadSize)
{
	position.y += snakeHeadSize * 2;
}

sf::Vector2f Water::getPosition()
{
	return position;
}

sf::Vector2f Water::getSize()
{
	return size;
}
