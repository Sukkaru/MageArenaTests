#include "stdafx.h"
#include "RockSlide.h"


RockSlide::RockSlide(sf::Vector2f initialpos, sf::Vector2f direction)
{
	m_moveSpeed =			1;
	m_velocity =			direction * m_moveSpeed;
	m_totalSpellLife =		1.5f;
	m_currentSpellLife =	0;
	m_spellcooldown =		0.3f;
	m_castCooldown =		0.f;

	m_spellBody.setPosition(initialpos);
	m_spellBody.setFillColor(sf::Color(150,50,0));
	m_spellBody.setRadius(40.0f);
	m_spellBody.setOrigin(m_spellBody.getRadius(), m_spellBody.getRadius());
}


RockSlide::~RockSlide()
{
}

void RockSlide::Update(sf::RenderWindow * window, sf::Time * dt)
{
	BaseSpell::Update(window, dt);
}

void RockSlide::Draw(sf::RenderWindow * window)
{
	window->draw(m_spellBody);
}

std::shared_ptr<BaseSpell> RockSlide::makeSpell(sf::Vector2f initialpos, sf::Vector2f direction)
{

	std::shared_ptr<RockSlide> instance(new RockSlide(initialpos, direction));
	return instance;
}
