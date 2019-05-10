#include "snake.h"

Snake::Snake(sf::Vector2f new_position, sf::Color new_color, int new_headSize, int new_playerNumber) : color(new_color), headSize(new_headSize), playerNumber(new_playerNumber)
{
	//Preset colours for each snake.
	switch (playerNumber)
	{
	case 1:
		color = sf::Color(5, 242, 219);
		break;
	case 2:
		color = sf::Color(242, 5, 159);
		break;
	case 3:
		color = sf::Color(171, 5, 242);
		break;
	case 4:
		color = sf::Color(238, 5, 242);
		break;
	}

	structSegment head;
	head.position = new_position;
	body.push_front(head);

	//Custom linked list version.
	/*sbody = new Segment(new_position);*/
}

Snake::~Snake()
{
	//Delete all contents of custom linked list.
	/*Clear();*/
}


void Snake::clearTarget()
{
}

void Snake::Render(sf::RenderWindow & window)
{
	for (auto &segment : body)
	{
		sf::CircleShape *shape = new sf::CircleShape((float)headSize);
		shape->setFillColor(color);
		shape->setPosition(segment.position);
		window.draw(*shape);
		delete shape;
	}

}

int Snake::getHeadSize() const
{
	return headSize;
}

sf::Vector2f Snake::getPosition() const
{
	structSegment temp = body.front();

	return temp.position;
}

void Snake::checkCollisions(const int &screenWidth, const int &screenHeight, const sf::Vector2f &waterPos, std::vector<Food>& allFood, std::vector <Snake*> &allPlayers)
{
	//Check Collisions with Self
	bool first = true;
	for (std::list<structSegment>::iterator it = body.begin(); it != body.end(); it++)
	{
		if (first)
		{
			first = false;
			continue;
		}

		if (body.front().position == it->position)
		{
			setDead();
		}
	}
	//Check collisopn with all other snakes.
	for (Snake* opponent : allPlayers)
	{
		//If the player number is different, check whether collides.
		if (opponent->getPlayerNumber() != this->getPlayerNumber())
		{
			//Iterate through the other players body, if any position collides with the head of the current snake, kill which has the lowest score.
			for (std::list<structSegment>::iterator it = opponent->body.begin(); it != opponent->body.end(); it++)
			{
				if (it->position == this->getPosition())
				{
					//Kill which has lowest score or both if same score
					if (opponent->getScore() > getScore())
					{
						setDead();

					}
					else if (opponent->getScore() == getScore())
					{
						opponent->setDead();
						setDead();

					}
					else
					{
						opponent->setDead();
					}
				}
			}
		}
	}
	//Check Collisions with Collectables	
	for (auto &food : allFood)
	{
		if (getPosition() == food.getPosition() && food.getState() == true)
		{
			/*Grow(food.getScore());*/
			growAmount = food.getScore();
			food.toggleAlive();
			food.generateNewValues(screenWidth, screenHeight, headSize);
			score += food.getScore();
		}
	}

	//If snake head is two spaces above the water line will shrink from the front. 
	if (body.front().position.y < (waterPos.y - (float)headSize * 2))
	{
		body.front().position.y = waterPos.y - ((float)headSize * 2);

		if (body.size() > 1)
		{
			body.pop_front();
		}
	}
	//Check wall collisions.
	if (body.front().position.x < 0 || body.front().position.x > screenWidth || body.front().position.y > screenHeight || body.size() == 0)
	{
		setDead();
	}

	//-------------------CUSTOM LINKED LIST VERSION---------------------------------------------------------------

	//currentSnakeSize = 0;
	////Check Collisions with Self

	//bool first = true;
	//Segment* sIter = body;
	//while (sIter->getNext() != nullptr)
	//{
	//	if (first)
	//	{
	//		first = false;
	//		currentSnakeSize++;
	//		continue;
	//	}

	//	if (body->getPosition() == sIter->getPosition())
	//	{
	//		setDead();
	//	}
	//	currentSnakeSize++;
	//}

	////Check collisopn with all other snakes.
	//for (Snake* opponent : allPlayers)
	//{
	//	//If the player number is different, check whether collides.
	//	if (opponent->getPlayerNumber() != this->getPlayerNumber())
	//	{
	//		//Iterate through the other players body, if any position collides with the head of the current snake, kill which has the lowest score.
	//		Segment* sIter = body;
	//		while (sIter->getNext() != nullptr)
	//		{
	//			if (sIter->getPosition() == this->getPosition())
	//			{
	//				//Kill which has lowest score or both if same score
	//				if (opponent->getScore() > getScore())
	//				{
	//					setDead();

	//				}
	//				else if (opponent->getScore() == getScore())
	//				{
	//					opponent->setDead();
	//					setDead();

	//				}
	//				else
	//				{
	//					opponent->setDead();
	//				}
	//			}
	//		}
	//	}
	//}

	//for (auto &food : allFood) //Check Collisions with Collectables	
	//{
	//	if (getPosition() == food.getPosition() && food.getState() == true)
	//	{
	//		/*Grow(food.getScore());*/
	//		growAmount = food.getScore();
	//		food.toggleAlive();
	//		food.generateNewValues(screenWidth, screenHeight, headSize);
	//		score += food.getScore();
	//	}
	//}

	////Add Water Levelling if go up for air. 

	//if (body->getPosition().y < (waterPos.y - (float)headSize * 2)) //If snake head is two spaces above the water line will shrink from the front. 
	//{
	//	body->setPositionY(waterPos.y - ((float)headSize * 2));

	//	if (currentSnakeSize > 1)
	//	{
	//		RemoveSegment();;
	//	}
	//}

	////Check wall collisions.

	//if (body->getPosition().x < 0 || body->getPosition().x > screenWidth || body->getPosition().y > screenHeight)
	//{
	//	setDead();
	//}

	//if (currentSnakeSize == 0)
	//{
	//	setDead();
	//}
}

int Snake::getScore()
{
	return score;
}

float Snake::getBreath()
{
	return breath;
}

bool Snake::getIsDead()
{
	return isDead;
}

int Snake::getPlayerNumber()
{
	return playerNumber;
}

sf::Color Snake::getColor()
{
	return color;
}

void Snake::Move(const int &screenWidth, const int &screenHeight)
{
	structSegment newSegment;
	newSegment.position.x = (body.front().position.x + xInc);
	newSegment.position.y = (body.front().position.y + yInc);

	//Adds new segment to front of the snake.
	body.push_front(newSegment);
	//By default growAmount is 0, increases with food.
	if (growAmount > 0)
	{
		growAmount--;
		clearTarget();
	}
	else
		//Removes segment from back of the snake.
	{
		body.pop_back();
	}

	//-------------------CUSTOM LINKED LIST VERSION---------------------------------------------------------------

	//sf::Vector2f newSegment;
	//newSegment.x = (body->getPosition().x + xInc);
	//newSegment.y = (body->getPosition().y + yInc);

	////Adds new segment to front of the snake.
	//AddSegment(newSegment);
	////By default growAmount is 0, increases with food.
	//if (growAmount > 0)
	//{
	//	growAmount--;
	//	clearTarget();
	//}
	//else
	//	//Removes segment from back of the snake.
	//{
	//	RemoveSegment();
	//}

}

void Snake::Shrink()
{
	if (body.size() > 1)
	{
		//Removes segment from back of the snake.
		body.pop_back();

		//------------------ - CUSTOM LINKED LIST VERSION-------------------------------------------------------------- 
		//RemoveSegment();
	}
	else
	{
		//If no body left to subtract, snake dies.
		isDead = true;
	}
}

void Snake::changeDirection(const sf::Vector2f &new_position)
{
	yInc = (int)new_position.y;
	xInc = (int)new_position.x;
}

void Snake::Breath(const sf::Vector2f &water)
{
	if (body.front().position.y > water.y)
	{
		breath -= breathInc;
	}

	else if (body.front().position.y < water.y)
	{
		breath = 100;
	}

	if (breath < 0)
	{
		Shrink();
	}

	//---------------------CUSTOM LINKED LIST----------------------------------------------------
	/*if (sbody->getPosition().y > water.y)
	{
		breath -= breathInc;
	}

	else if (sbody->getPosition().y < water.y)
	{
		breath = 100;
	}*/
}

void Snake::setDead()
{
	breath = 0;
	isDead = true;
}

//--------------------FUNCTIONS EXCLUSIVE TO CUSTOM LINKED LIST---------------------------------




