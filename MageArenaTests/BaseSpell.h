#pragma once
#include "PhysicsObject.h"
class BaseSpell : public PhysicsObject
{
public:
	BaseSpell();
	~BaseSpell();
	void virtual		Update(sf::RenderWindow* window, sf::Time* dt);
	void virtual		Draw(sf::RenderWindow* window);
	virtual std::shared_ptr<BaseSpell> getSpell(sf::Vector2f initialpos, sf::Vector2f direction) {};

	float				getSpellCooldown();


protected:
	float				m_spellcooldown = 1.f;
	float				m_totalSpellLife;
	float				m_currentSpellLife;
};

