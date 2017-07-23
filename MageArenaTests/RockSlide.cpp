#include "stdafx.h"
#include "RockSlide.h"


RockSlide::RockSlide(sf::Vector2f initialPosition, sf::Vector2f direction)
{

	m_destroyed =				false;
	m_moveSpeed =				1;
	m_velocity =				direction * m_moveSpeed;
	m_totalSpellLife =			3.8f;
	m_currentSpellLife =		0;
	m_spellCooldown =			0.8f;
	m_castCooldown =			0.f;
	m_moveSpellBody =			.15f;
	m_moveSpellBodyTimer =		0.f;
	m_moveSpellDistance =		50.f;
	m_moveCount =				0;
	m_maxMoveCount =			8;

	m_spellsRadius = 40.f;

	m_previousPosition = initialPosition;		//Added this so shadowOne on the first update doesn't appear at position (0,0)

	m_spellBody.setPosition(initialPosition);
	m_spellBody.setFillColor(sf::Color(150,50,0));
	m_spellBody.setRadius(m_spellsRadius);
	m_spellBody.setOrigin(m_spellBody.getRadius(), m_spellBody.getRadius());

	//Collision stuff
	m_boundingBox = m_spellBody.getGlobalBounds();
	m_previousBoundingBox = m_boundingBox;

	//Stuff for the lasting circle effect
	m_shadowOne.setPosition(initialPosition);
	m_shadowOne.setFillColor(sf::Color(150, 50, 0));
	m_shadowOne.setRadius(m_spellsRadius);
	m_shadowOne.setOrigin(m_spellBody.getRadius(), m_spellBody.getRadius());
	
	m_shadowTwo.setPosition(initialPosition);
	m_shadowTwo.setFillColor(sf::Color(150, 50, 0));
	m_shadowTwo.setRadius(m_spellsRadius);
	m_shadowTwo.setOrigin(m_spellBody.getRadius(), m_spellBody.getRadius());
}


RockSlide::~RockSlide()
{
}

void RockSlide::update(sf::RenderWindow * window, sf::Time * dt)
{
	BaseSpell::update(window, dt);

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
			m_previousBoundingBox = m_boundingBox;
			m_spellBody.move(m_velocity * m_moveSpellDistance);
			m_boundingBox = m_spellBody.getGlobalBounds();
		}
		m_moveSpellBodyTimer = 0.f;
		m_moveCount++;
	}


		BaseSpell::update(window, dt);	//Why is this called twice? 
}

void RockSlide::draw(sf::RenderWindow * window)
{
	window->draw(m_spellBody);
	window->draw(m_shadowOne);
	window->draw(m_shadowTwo);

}

std::shared_ptr<BaseSpell> RockSlide::makeSpell(sf::Vector2f initialPosition, sf::Vector2f direction)
{


	std::shared_ptr<RockSlide> instance(new RockSlide(initialPosition, direction));

	return instance;
}

void RockSlide::resolveCollision(std::shared_ptr<PhysicsObject> otherObject, sf::FloatRect collisionRect)
{
	switch (otherObject->getCollisionGroup())
	{
	case 2:					//Terrain
		m_destroyed = true;	//Destroy the spell when it hits terrain
		break;
	}
}
