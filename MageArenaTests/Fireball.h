#pragma once
#include "BaseSpell.h"
class Fireball : public BaseSpell
{
public:
	Fireball(sf::Vector2f initialpos, sf::Vector2f direction);
	~Fireball();
	void virtual				Update(sf::RenderWindow* window, sf::Time* dt);
	void virtual				Draw(sf::RenderWindow* window);
	std::shared_ptr<BaseSpell>	makeSpell(sf::Vector2f initialpos, sf::Vector2f direction);
	void virtual				resolveCollision(std::shared_ptr<PhysicsObject> otherobject);

private:
	sf::CircleShape				m_spellBody;
	
};

