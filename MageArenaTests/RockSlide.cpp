#include "stdafx.h"
#include "RockSlide.h"


RockSlide::RockSlide(sf::Vector2f initialpos, sf::Vector2f direction)
{

	m_destroyed =				false;
	m_moveSpeed =				1;
	m_velocity =				direction * m_moveSpeed;
	m_totalSpellLife =			3.8f;
	m_currentSpellLife =		0;
	m_spellcooldown =			0.8f;
	m_castCooldown =			0.f;
	m_moveSpellBody =			.15f;
	m_moveSpellBodyTimer =		0.f;
	m_moveSpellDistance =		50.f;
	m_moveCount =				0;
	m_maxMoveCount =			8;

	m_spellsRadius = 40.f;

	m_spellBody.setPosition(initialpos);
	m_spellBody.setFillColor(sf::Color(150,50,0));
	m_spellBody.setRadius(m_spellsRadius);
	m_spellBody.setOrigin(m_spellBody.getRadius(), m_spellBody.getRadius());

	//Stuff for the lasting circle effect
	m_shadowOne.setPosition(initialpos);
	m_shadowOne.setFillColor(sf::Color(150, 50, 0));
	m_shadowOne.setRadius(m_spellsRadius);
	m_shadowOne.setOrigin(m_spellBody.getRadius(), m_spellBody.getRadius());
	
	m_shadowTwo.setPosition(initialpos);
	m_shadowTwo.setFillColor(sf::Color(150, 50, 0));
	m_shadowTwo.setRadius(m_spellsRadius);
	m_shadowTwo.setOrigin(m_spellBody.getRadius(), m_spellBody.getRadius());
}


RockSlide::~RockSlide()
{
}

void RockSlide::Update(sf::RenderWindow * window, sf::Time * dt)
{
	BaseSpell::Update(window, dt);

	m_moveSpellBodyTimer += dt->asSeconds();
	
	//move the shadow circles to the main circles old position
	if (m_moveCount % 2 == 0)
	{
		m_shadowOne.setPosition(m_previousPosition);
	}
	else 
	{
		m_shadowTwo.setPosition(m_previousPosition);
	}

	//main circles jumpy behaviour
	if (m_moveSpellBodyTimer > m_moveSpellBody)
	{
		m_previousPosition = m_spellBody.getPosition();
		if (m_moveCount < m_maxMoveCount)
		{
			m_spellBody.move(m_velocity * m_moveSpellDistance);
		}
		m_moveSpellBodyTimer = 0.f;
		m_moveCount++;
	}


		BaseSpell::Update(window, dt);
}

void RockSlide::Draw(sf::RenderWindow * window)
{
	window->draw(m_spellBody);
	window->draw(m_shadowOne);
	window->draw(m_shadowTwo);

}

std::shared_ptr<BaseSpell> RockSlide::makeSpell(sf::Vector2f initialpos, sf::Vector2f direction, std::vector<std::shared_ptr<GameObject>> &gameVec)
{


	std::shared_ptr<RockSlide> instance(new RockSlide(initialpos, direction));

	return instance;
}
