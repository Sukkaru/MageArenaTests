#include "stdafx.h"
#include "Fireball.h"


Fireball::Fireball(sf::Vector2f direction)
{
	m_spellBody.setFillColor(sf::Color::Red);
	m_spellBody.setRadius(20.0f);
	m_moveSpeed = 1000;
	m_velocity = direction * m_moveSpeed;

}


Fireball::~Fireball()
{
}

void Fireball::Update(sf::RenderWindow * window, sf::Time* dt)
{
	m_spellBody.setPosition(m_spellBody.getPosition() + m_velocity * dt->asSeconds());
}

void Fireball::Draw(sf::RenderWindow * window)
{
	window->draw(m_spellBody);
}
