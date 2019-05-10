#include <SFML/Graphics.hpp>
#include "rectangle.h"
#include "time.h"


Rectangle::Rectangle(const sf::Vector2f & new_position, const sf::Color & new_color, const int & new_width, const int & new_height) : Shape(new_position, new_color), width(new_width), height(new_height)
{
}

void Rectangle::Render(sf::RenderWindow & window)
{


	sf::RectangleShape *shape = new sf::RectangleShape();
	sf::Vector2f *size = new sf::Vector2f(width,height);

	shape->setSize(*size); 
	   
	
	shape->setFillColor(color);

	shape->setPosition(position);

	shape->setRotation(rotation);

	//xInc = 0;	//Movement direction -1, 0 , 1
	//yInc = -1;

	//speed = rand() % 5 + 2;

	//position.x += xInc * speed;
	//position.y += yInc * speed;

	//// Check if off edges, if so - bounce and change speed
	//if (position.x < 0 || position.x >= window.getSize().x)
	//{
	//	xInc = -xInc;
	//	
	//}

	//if (position.y < 0 || position.y >= window.getSize().y)
	//{
	//	yInc = -yInc;
	//	
	//}

	

	window.draw(*shape);

	delete size;
	delete shape;
}

//void Rectangle::Grow(float multiplier)
//{
//	this-> height = height * multiplier;
//	this->width = width * multiplier;
//}
//
//void Rectangle::Shrink(float multiplier)
//{
//	this->height = height / multiplier;
//	this->width = width / multiplier;
//	
//}



