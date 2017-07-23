#pragma once
#include "PhysicsObject.h"
class Enemy : public PhysicsObject
{
public:
	Enemy(std::vector<std::shared_ptr<GameObject>>* gameObjVector);
	~Enemy();
	void virtual update(sf::RenderWindow* window, sf::Time* dt);
	void virtual draw(sf::RenderWindow* window);
private:
	sf::RectangleShape			m_enemyBody;
};

