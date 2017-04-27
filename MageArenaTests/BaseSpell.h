#pragma once
#include "PhysicsObject.h"
class BaseSpell : public PhysicsObject
{
public:
	BaseSpell();
	~BaseSpell();
	void virtual		Update(sf::RenderWindow* window, sf::Time* dt);
	void virtual		Draw(sf::RenderWindow* window);

	float				getSpellCooldown();

protected:
	float				m_spellcooldown = 1.f;

};

