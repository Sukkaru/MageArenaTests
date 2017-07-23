#pragma once
#include "PhysicsObject.h"
class BaseSpell : public PhysicsObject
{
public:
	BaseSpell();
	~BaseSpell();
	void virtual						update(sf::RenderWindow* window, sf::Time* dt);
	void virtual						draw(sf::RenderWindow* window);
	std::shared_ptr<BaseSpell> virtual	makeSpell(sf::Vector2f initialPosition, sf::Vector2f direction);
	void virtual						resolveCollision(std::shared_ptr<PhysicsObject> otherObject, sf::FloatRect collisionRect);

	float								getSpellCooldown();
	float								getCurrentCastCooldown();
	void								resetCastCooldown();
	void								increaseCastCooldown(float dt);


protected:
	float								m_spellCooldown;
	float								m_totalSpellLife;
	float								m_currentSpellLife;
	float								m_castCooldown;
};

