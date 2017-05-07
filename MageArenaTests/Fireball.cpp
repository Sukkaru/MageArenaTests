#include "stdafx.h"
#include "Fireball.h"


Fireball::Fireball(sf::Vector2f direction, sf::Vector2f initialpos)
{
	m_spellBody.setFillColor(sf::Color::Red);
	m_spellBody.setRadius(15.0f);
	m_spellBody.setOrigin(m_spellBody.getRadius(), m_spellBody.getRadius());
	m_spellBody.setPosition(initialpos);
	m_moveSpeed =	1000;
	m_velocity =	direction * m_moveSpeed;
	m_totalSpellLife =	0.2f;
	m_currentSpellLife = 0;

}


Fireball::~Fireball()
{
}

void Fireball::Update(sf::RenderWindow * window, sf::Time* dt)
{
	m_spellBody.setPosition(m_spellBody.getPosition() + m_velocity * dt->asSeconds());
	m_currentSpellLife += dt->asSeconds();
	if (m_currentSpellLife >= m_totalSpellLife)
	{
		setDestroyed(true);
	}


}

void Fireball::Draw(sf::RenderWindow * window)
{
	window->draw(m_spellBody);
}


