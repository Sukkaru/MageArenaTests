#pragma once
#include "BaseSpell.h"
class Fireball : public BaseSpell
{
public:
	Fireball(sf::Vector2f direction,sf::Vector2f initialpos);
	~Fireball();
	void virtual		Update(sf::RenderWindow* window, sf::Time* dt);
	void virtual		Draw(sf::RenderWindow* window);

private:
	sf::CircleShape		m_spellBody;
};

