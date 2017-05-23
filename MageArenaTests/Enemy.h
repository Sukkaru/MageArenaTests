#pragma once
#include "PhysicsObject.h"
class Enemy : public PhysicsObject
{
public:
	Enemy(std::vector<std::shared_ptr<GameObject>>* p_vec);
	~Enemy();
	void virtual Update(sf::RenderWindow* window, sf::Time* dt);
	void virtual Draw(sf::RenderWindow* window);
private:
	sf::RectangleShape			m_enemybody;
};

