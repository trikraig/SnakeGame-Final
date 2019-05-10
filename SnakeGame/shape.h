#pragma once
#include <SFML/Graphics.hpp>

class Shape
{
protected:

	sf::Vector2f position;
	sf::Color color;
	float rotation;
	int xInc{ 12 }; 
	int yInc{ 0 };
	
	
	

public:

	Shape(sf::Vector2f new_position, sf::Color new_color);
	virtual void Render(sf::RenderWindow& window) = 0;


	void Move();
	void MoveToPos(sf::Vector2f new_position);


	};
