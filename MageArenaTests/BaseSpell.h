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
	bool				getDestroyed() { return m_destroyed; }
	void				setDestroyed(bool input) { m_destroyed = input; }

protected:
	float				m_spellcooldown = 1.f;
	bool				m_destroyed = false;
	float				m_totalSpellLife;
	float				m_currentSpellLife;
};

