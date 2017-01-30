#pragma once
#include "PhysicsObject.h"
class Enemy : public PhysicsObject
{
public:
	Enemy();
	~Enemy();
	void virtual Update(sf::RenderWindow* window, sf::Clock* clock);
	void virtual Draw(sf::RenderWindow* window);
private:
	sf::RectangleShape m_enemyBody;
};

