#pragma once
#include "BaseSpell.h"
class RockSlide :
	public BaseSpell
{
public:
	RockSlide(sf::Vector2f initialpos, sf::Vector2f direction, std::vector<std::shared_ptr<GameObject>> &gameVec, int castCout);
	~RockSlide();
	void virtual				Update(sf::RenderWindow* window, sf::Time* dt);
	void virtual				Draw(sf::RenderWindow* window);
	std::shared_ptr<BaseSpell>	makeSpell(sf::Vector2f initialpos, sf::Vector2f direction);


private:
	sf::CircleShape				m_spellBody;

	                                      

};

