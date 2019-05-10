#include "cpuSnake.h"

cpuSnake::cpuSnake(sf::Vector2f new_position, sf::Color new_color, int new_headSize, int new_playerNumber) : Snake(new_position, new_color, new_headSize, new_playerNumber)
{
}

void cpuSnake::Update(std::vector<Food>& allFood, std::vector<Snake*>& allPlayers)
{
	currentPosSquared.x = pow(getPosition().x, 2);
	currentPosSquared.y = pow(getPosition().y, 2);

	currentTargetSquared.x = pow(currentTarget.x, 2);
	currentTargetSquared.y = pow(currentTarget.y, 2);

	if (breath < breathThreshold)
	{
		needsAir = true;
	}
	else
	{
		needsAir = false;
	}

	//Overrides the search for food to just go up for air.
	switch (needsAir)
	{
	case true:

		directionOne = EDirection::eNorth;
		break;

	case false:

		if (targetSet == true)
		{
			targetSet = false;

			for (Food &food : allFood)
			{
				if (currentTarget.x == food.getPosition().x && currentTarget.y == food.getPosition().y)
				{
					targetSet = true;
					break;
				}
			}

		}
		//Loops through food, finds the closest and sets as the current target. Does not change until food has been eaten.
		for (Food &food : allFood)
		{

			if (food.getState() == true && targetSet == false)
			{
				sf::Vector2f currentFoodSquared;
				currentFoodSquared.x = pow(food.getPosition().x, 2);
				currentFoodSquared.y = pow(food.getPosition().y, 2);

				if ((currentPosSquared.x - currentFoodSquared.x) < currentTargetSquared.x && (currentPosSquared.y - currentFoodSquared.y) < currentTargetSquared.y)
				{
					currentTarget.x = sqrt(currentFoodSquared.x);
					currentTarget.y = sqrt(currentFoodSquared.y);
					targetSet = true;
				}
			}
		}

		//Controls direction of snake relative to the target food.
		if (getPosition().y < currentTarget.y && previousDirection != EDirection::eNorth)
		{
			targetRelativeToPos = EDirection::eSouth;
		}

		if (getPosition().y > currentTarget.y && previousDirection != EDirection::eSouth)
		{
			targetRelativeToPos = EDirection::eNorth;
		}

		if (getPosition().x < currentTarget.x && previousDirection != EDirection::eWest)
		{
			targetRelativeToPos = EDirection::eEast;
		}

		if (getPosition().x > currentTarget.x && previousDirection != EDirection::eEast)
		{
			targetRelativeToPos = EDirection::eWest;
		}


		switch (targetRelativeToPos)
		{
		case EDirection::eNorth:
			if (previousDirection == EDirection::eSouth)
			{
				directionOne = EDirection::eWest;
			}
			else
			{
				directionOne = EDirection::eNorth;
			}
			break;
		case EDirection::eEast:
			if (previousDirection == EDirection::eWest)
			{
				directionOne = EDirection::eSouth;
			}
			else
			{
				directionOne = EDirection::eEast;
			}
			break;
		case EDirection::eSouth:
			if (previousDirection == EDirection::eNorth)
			{
				directionOne = EDirection::eEast;
			}
			else
			{
				directionOne = EDirection::eSouth;
			}
			break;
		case EDirection::eWest:
			if (previousDirection == EDirection::eEast)
			{
				directionOne = EDirection::eSouth;
			}
			else
			{
				directionOne = EDirection::eWest;
			}
			break;
		}

	}
	//Converts direction to vector.
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
	//Prevents snake going back on itself.
	previousDirection = directionOne;
}

void cpuSnake::clearTarget()
{
	targetSet = false;
}
