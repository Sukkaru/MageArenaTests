#include "stdafx.h"
#include "Waterhose.h"


Waterhose::Waterhose(sf::Vector2f initialPosition, sf::Vector2f direction)
{
	m_destroyed = false;
	m_moveSpeed = 1200;
	m_velocity = direction * m_moveSpeed;
	m_totalSpellLife = 0.26f;
	m_currentSpellLife = 0;
	m_spellCooldown = 0.05f;	//0.05
	m_castCooldown = 0.f;
	m_waveScaler = 1.1f;

	m_spellBody.setPosition(initialPosition);
	m_spellBody.setFillColor(sf::Color::Blue);
	m_spellBody.setRadius(12.0f);
	m_spellBody.setOrigin(m_spellBody.getRadius(), m_spellBody.getRadius());

	//Collision stuff
	m_boundingBox = m_spellBody.getGlobalBounds();
	m_previousBoundingBox = m_boundingBox;
}


Waterhose::~Waterhose()
{
}

void Waterhose::update(sf::RenderWindow * window, sf::Time * dt)
{
	BaseSpell::update(window, dt);
	m_previousBoundingBox = m_boundingBox;
	m_spellBody.setPosition(m_spellBody.getPosition() + m_velocity * dt->asSeconds());
	m_boundingBox = m_spellBody.getGlobalBounds();
	m_spellBody.scale(m_waveScaler, m_waveScaler);
}

void Waterhose::draw(sf::RenderWindow * window)
{
	window->draw(m_spellBody);
}

std::shared_ptr<BaseSpell> Waterhose::makeSpell(sf::Vector2f initialPosition, sf::Vector2f direction)
{
	std::shared_ptr<Waterhose> instance(new Waterhose(initialPosition, direction));
	return instance;
}

void Waterhose::resolveCollision(std::shared_ptr<PhysicsObject> otherObject, sf::FloatRect collisionRect)
{
	switch (otherObject->getCollisionGroup())
	{
	case 2:					//Terrain
		m_destroyed = true;	//Destroy the spell when it hits terrain
		break;
	}
}
