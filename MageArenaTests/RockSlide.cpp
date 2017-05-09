#include "stdafx.h"
#include "RockSlide.h"


RockSlide::RockSlide(sf::Vector2f initialpos, sf::Vector2f direction, std::vector<std::shared_ptr<GameObject>> &gameVec, int castCout)
{
	m_moveSpeed =			1;
	m_velocity =			direction * m_moveSpeed;
	m_totalSpellLife =		1.5f;
	m_currentSpellLife =	0;
	m_spellcooldown =		1.f;
	m_castCooldown =		0.f;

	m_spellBody.setPosition(initialpos);
	// the rbg color code is a brownish
	m_spellBody.setFillColor(sf::Color(130,70,0));
	m_spellBody.setRadius(20.0f);
	m_spellBody.setOrigin(m_spellBody.getRadius(), m_spellBody.getRadius());
}


RockSlide::~RockSlide()
{
}

void RockSlide::Update(sf::RenderWindow * window, sf::Time * dt)
{
}

void RockSlide::Draw(sf::RenderWindow * window)
{
}

std::shared_ptr<BaseSpell> RockSlide::makeSpell(sf::Vector2f initialpos, sf::Vector2f direction)
{
	return std::shared_ptr<BaseSpell>();
}
