#include "stdafx.h"
#include "Fireball.h"


Fireball::Fireball(sf::Vector2f initialPosition, sf::Vector2f direction)
{
	m_destroyed = false;

	m_moveSpeed =			1000;
	m_velocity =			direction * m_moveSpeed;
	m_totalSpellLife =		1.5f;
	m_currentSpellLife =	0;
	m_spellCooldown =		0.3f;
	m_castCooldown =		0.f;

	m_spellBody.setPosition(initialPosition);
	m_spellBody.setFillColor(sf::Color::Red);
	m_spellBody.setRadius(12.0f);
	m_spellBody.setOrigin(m_spellBody.getRadius(), m_spellBody.getRadius());

	//Collision stuff
	m_boundingBox = m_spellBody.getGlobalBounds();
	m_previousBoundingBox = m_boundingBox;
}


Fireball::~Fireball()
{
}

void Fireball::update(sf::RenderWindow * window, sf::Time* dt)
{
	BaseSpell::update(window, dt);
	m_previousBoundingBox = m_boundingBox;
	m_spellBody.setPosition(m_spellBody.getPosition() + m_velocity * dt->asSeconds());
	m_boundingBox = m_spellBody.getGlobalBounds();

}

void Fireball::draw(sf::RenderWindow * window)
{
	window->draw(m_spellBody);
}

std::shared_ptr<BaseSpell> Fireball::makeSpell(sf::Vector2f initialPosition, sf::Vector2f direction)
{
	
	std::shared_ptr<Fireball> instance(new Fireball(initialPosition, direction));
	return instance;
}

void Fireball::resolveCollision(std::shared_ptr<PhysicsObject> otherObject, sf::FloatRect collisionRect)
{
	//Do damage eventually

	//Set the fireball to be destroyed
	m_destroyed = true;
}


