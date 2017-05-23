#include "stdafx.h"
#include "BaseSpell.h"


BaseSpell::BaseSpell()
{
	m_collisiongroup = 4;
	m_collidablegroups = 12;
}


BaseSpell::~BaseSpell()
{
}

void BaseSpell::Update(sf::RenderWindow * window, sf::Time* dt)
{
	m_currentSpellLife += dt->asSeconds();
	if (m_currentSpellLife >= m_totalSpellLife)
	{
		setDestroyed(true);
	}
}

void BaseSpell::Draw(sf::RenderWindow * window)
{
}

float BaseSpell::getSpellCooldown()
{
	return m_spellcooldown;
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
