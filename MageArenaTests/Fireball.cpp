#include "stdafx.h"
#include "Fireball.h"


Fireball::Fireball(sf::Vector2f initialpos, sf::Vector2f direction)
{
	m_moveSpeed =	1000;
	m_velocity =	direction * m_moveSpeed;
	m_spellBody.setPosition(initialpos);
	m_spellBody.setFillColor(sf::Color::Red);
	m_spellBody.setRadius(15.0f);
	m_spellBody.setOrigin(m_spellBody.getRadius(), m_spellBody.getRadius());
	m_totalSpellLife =	1.5f;
	m_currentSpellLife = 0;

	printf("created fireball\n");

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

std::shared_ptr<BaseSpell> Fireball::getSpell(sf::Vector2f initialpos, sf::Vector2f direction)
{
	
	std::shared_ptr<Fireball> instance(new Fireball(initialpos, direction));
	return instance;
}


