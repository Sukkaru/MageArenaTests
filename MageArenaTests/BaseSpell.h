#pragma once
#include "PhysicsObject.h"
class BaseSpell : public PhysicsObject
{
public:
	BaseSpell();
	~BaseSpell();
	void virtual						Update(sf::RenderWindow* window, sf::Time* dt);
	void virtual						Draw(sf::RenderWindow* window);
	std::shared_ptr<BaseSpell> virtual	makeSpell(sf::Vector2f initialpos, sf::Vector2f direction) { return nullptr; }
	//std::shared_ptr<BaseSpell>	makeSpell(sf::Vector2f initialpos, sf::Vector2f direction, std::vector<std::shared_ptr<GameObject>> &gameVec, int castCount = 0) { return nullptr; }
	void virtual						resolveCollision(std::shared_ptr<PhysicsObject> otherobject);

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

