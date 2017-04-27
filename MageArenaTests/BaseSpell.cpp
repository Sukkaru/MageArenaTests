#include "stdafx.h"
#include "BaseSpell.h"


BaseSpell::BaseSpell()
{
}


BaseSpell::~BaseSpell()
{
}

void BaseSpell::Update(sf::RenderWindow * window, sf::Time* dt)
{
}

void BaseSpell::Draw(sf::RenderWindow * window)
{
}

float BaseSpell::getSpellCooldown()
{
	return m_spellcooldown;
}
