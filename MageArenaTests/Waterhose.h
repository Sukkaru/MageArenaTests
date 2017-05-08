#pragma once
#include "BaseSpell.h"
class Waterhose : public BaseSpell
{
public:
	Waterhose(sf::Vector2f initialpos, sf::Vector2f direction);
	~Waterhose();
	void virtual				Update(sf::RenderWindow* window, sf::Time* dt);
	void virtual				Draw(sf::RenderWindow* window);
	std::shared_ptr<BaseSpell>	makeSpell(sf::Vector2f initialpos, sf::Vector2f direction);

private:
	sf::CircleShape				m_spellBody;
	float						m_waveScaler = 1.0015f;
};

