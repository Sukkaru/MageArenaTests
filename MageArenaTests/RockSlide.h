#pragma once
#include "BaseSpell.h"
class RockSlide :
	public BaseSpell
{
public:
	RockSlide(sf::Vector2f initialPosition, sf::Vector2f direction);
	~RockSlide();
	void virtual				update(sf::RenderWindow* window, sf::Time* dt);
	void virtual				draw(sf::RenderWindow* window);
	std::shared_ptr<BaseSpell> 	makeSpell(sf::Vector2f initialPosition, sf::Vector2f direction);
	void virtual				resolveCollision(std::shared_ptr<PhysicsObject> otherObject, sf::FloatRect collisionRect);

private:
	float						m_spellsRadius;

	sf::CircleShape				m_spellBody;
	sf::CircleShape				m_shadowOne;
	sf::CircleShape				m_shadowTwo;
	sf::Vector2f				m_previousPosition;

	float						m_moveSpellBody;
	float						m_moveSpellBodyTimer;
	float						m_moveSpellDistance;
	int							m_moveCount;
	int							m_maxMoveCount;
};

