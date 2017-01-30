#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"
class GameManager
{
public:
	GameManager();
	~GameManager();
	void Update(sf::RenderWindow* window, sf::Clock * clock);
	void Draw(sf::RenderWindow* window);
private:
	Player m_mage;
	Enemy m_enemy;
};

