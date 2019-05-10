#include "player.h"

Player::Player(sf::Vector2f new_position, sf::Color new_color, int new_headSize, int new_playerNumber) : Snake(new_position, new_color, new_headSize, new_playerNumber)
{
}

void Player::Update(std::vector<Food>& allFood, std::vector<Snake*> &allPlayers)
{
	//Alternate controls for each playable snake. 
	switch (playerNumber)
	{

	case 1:

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			if (directionOne != EDirection::eEast)
			{
				directionOne = EDirection::eWest;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			if (directionOne != EDirection::eWest)
			{
				directionOne = EDirection::eEast;
			}

		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			if (directionOne != EDirection::eSouth)
			{
				directionOne = EDirection::eNorth;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			if (directionOne != EDirection::eNorth)
			{
				directionOne = EDirection::eSouth;
			}

		}

		break;

	case 2:

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			if (directionOne != EDirection::eEast)
			{
				directionOne = EDirection::eWest;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			if (directionOne != EDirection::eWest)
			{
				directionOne = EDirection::eEast;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			if (directionOne != EDirection::eSouth)
			{
				directionOne = EDirection::eNorth;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			if (directionOne != EDirection::eNorth)
			{
				directionOne = EDirection::eSouth;
			}
		}

		break;

	}

	//Takes the desired direction for each player and converts to a vector.
	switch (directionOne)
	{


	case EDirection::eNorth:
		changeDirection(sf::Vector2f(0, -h));


		break;
	case EDirection::eWest:
		changeDirection(sf::Vector2f(-h, 0));

		break;
	case EDirection::eEast:
		changeDirection(sf::Vector2f(h, 0));

		break;
	case EDirection::eSouth:
		changeDirection(sf::Vector2f(0, h));

		break;
	}
}
