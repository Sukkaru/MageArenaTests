#pragma once
#include "PhysicsObject.h"
class BaseSpell : public PhysicsObject
{
public:
	BaseSpell();
	~BaseSpell();
	void virtual Update(sf::RenderWindow* window, sf::Clock* clock);
	void virtual Draw(sf::RenderWindow* window);
};

