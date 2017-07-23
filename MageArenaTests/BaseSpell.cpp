#include "stdafx.h"
#include "BaseSpell.h"


BaseSpell::BaseSpell()
{
	//Collision stuff
	m_collisionGroup = 4;
	m_collidableGroups = 12;
}


BaseSpell::~BaseSpell()
{
}

void BaseSpell::update(sf::RenderWindow * window, sf::Time* dt)
{
	m_currentSpellLife += dt->asSeconds();
	if (m_currentSpellLife >= m_totalSpellLife)
	{
		setDestroyed(true);
	}
}

void BaseSpell::draw(sf::RenderWindow * window)
{
}

std::shared_ptr<BaseSpell> BaseSpell::makeSpell(sf::Vector2f initialPosition, sf::Vector2f direction)
{
	return nullptr;
}

void BaseSpell::resolveCollision(std::shared_ptr<PhysicsObject> otherObject, sf::FloatRect collisionRect)
{

}

float BaseSpell::getSpellCooldown()
{
	return m_spellCooldown;
}

float BaseSpell::getCurrentCastCooldown()
{
	return m_castCooldown;
}

void BaseSpell::increaseCastCooldown(float dt)
{
	m_castCooldown += dt;
}

void BaseSpell::resetCastCooldown()
{
	m_castCooldown = 0.f;
}
