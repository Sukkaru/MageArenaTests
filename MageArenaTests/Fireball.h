#pragma once
#include "BaseSpell.h"
class Fireball : public BaseSpell
{
public:
	Fireball(sf::Vector2f direction);
	~Fireball();
	void virtual Update(sf::RenderWindow* window, sf::Clock* clock);
	void virtual Draw(sf::RenderWindow* window);

private:
	sf::CircleShape m_spellBody;
};

