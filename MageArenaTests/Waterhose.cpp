#include "stdafx.h"
#include "Waterhose.h"


Waterhose::Waterhose(sf::Vector2f initialpos, sf::Vector2f direction)
{
	m_destroyed = false;
	m_moveSpeed = 1200;
	m_velocity = direction * m_moveSpeed;
	m_totalSpellLife = 0.26f;
	m_currentSpellLife = 0;
	m_spellcooldown = 0.05f;
	m_castCooldown = 0.f;
	m_waveScaler = 1.004f;

	m_spellBody.setPosition(initialpos);
	m_spellBody.setFillColor(sf::Color::Blue);
	m_spellBody.setRadius(12.0f);
	m_spellBody.setOrigin(m_spellBody.getRadius(), m_spellBody.getRadius());
}


Waterhose::~Waterhose()
{
}

void Waterhose::Update(sf::RenderWindow * window, sf::Time * dt)
{
	BaseSpell::Update(window, dt);
	m_spellBody.setPosition(m_spellBody.getPosition() + m_velocity * dt->asSeconds());
	//m_spellBody.setRadius(m_spellBody.getRadius() + (dt->asSeconds() * m_waveScaler));
	m_spellBody.scale(m_waveScaler, m_waveScaler);
}

void Waterhose::Draw(sf::RenderWindow * window)
{
	window->draw(m_spellBody);
}

std::shared_ptr<BaseSpell> Waterhose::makeSpell(sf::Vector2f initialpos, sf::Vector2f direction)
{
	std::shared_ptr<Waterhose> instance(new Waterhose(initialpos, direction));
	return instance;
}
