#include <SFML/Graphics.hpp>
#include "shape.h"

//void Shape::Render(sf::RenderWindow & window)
//{
//}

Shape::Shape(sf::Vector2f new_position, sf::Color new_color) : position (new_position) , color (new_color)
{
	
}



void Shape::Render(sf::RenderWindow & window)
{
}

//void Shape::Grow(float multiplier)
//{
//}

void Shape::Move()
{
	
	position.x += xInc;
	position.y += yInc;
	
}

void Shape::MoveToPos(sf::Vector2f new_position)
{
	
	yInc = new_position.y;
	xInc = new_position.x;
	
}



