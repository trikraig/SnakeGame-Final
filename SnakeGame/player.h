#pragma once
#include "snake.h"

class Player : public Snake {

public :

	Player(sf::Vector2f new_position, sf::Color new_color, int new_headSize, int new_playerNumber);
	void Update(std::vector<Food>& allFood, std::vector<Snake*> &allPlayers) override;

};
