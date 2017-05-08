#include "stdafx.h"
#include "Fireball.h"


Fireball::Fireball(sf::Vector2f initialpos, sf::Vector2f direction)
{
	m_moveSpeed =			1000;
	m_velocity =			direction * m_moveSpeed;
	m_totalSpellLife =		1.5f;
	m_currentSpellLife =	0;
	m_spellcooldown =		0.5f;
	m_castCooldown =		10.f;

	m_spellBody.setPosition(initialpos);
	m_spellBody.setFillColor(sf::Color::Red);
	m_spellBody.setRadius(12.0f);
	m_spellBody.setOrigin(m_spellBody.getRadius(), m_spellBody.getRadius());
}


Fireball::~Fireball()
{
}

void Fireball::Update(sf::RenderWindow * window, sf::Time* dt)
{
	BaseSpell::Update(window, dt);
	m_spellBody.setPosition(m_spellBody.getPosition() + m_velocity * dt->asSeconds());


}

void Fireball::Draw(sf::RenderWindow * window)
{
	window->draw(m_spellBody);
}

std::shared_ptr<BaseSpell> Fireball::makeSpell(sf::Vector2f initialpos, sf::Vector2f direction)
{
	
	std::shared_ptr<Fireball> instance(new Fireball(initialpos, direction));
	return instance;
}


