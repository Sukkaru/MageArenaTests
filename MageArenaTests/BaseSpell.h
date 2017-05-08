#pragma once
#include "PhysicsObject.h"
class BaseSpell : public PhysicsObject
{
public:
	BaseSpell();
	~BaseSpell();
	void virtual						Update(sf::RenderWindow* window, sf::Time* dt);
	void virtual						Draw(sf::RenderWindow* window);
	virtual std::shared_ptr<BaseSpell>	makeSpell(sf::Vector2f initialpos, sf::Vector2f direction) = 0;

	float								getSpellCooldown();
	float								getCurrentCastCooldown();
	void								resetCastCooldown();
	void								increaseCastCooldown(float dt);


protected:
	float								m_spellcooldown;
	float								m_totalSpellLife;
	float								m_currentSpellLife;
	float								m_castCooldown;
};

