#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy(std::vector<std::shared_ptr<GameObject>>* p_vec)
{
	m_destroyed = false;
	m_bbox.setSize(sf::Vector2f(50, 50));
	m_bbox.setOrigin(m_bbox.getSize().x / 2, m_bbox.getSize().y / 2);
	m_bbox.setFillColor(sf::Color::Blue);
	m_bbox.setPosition(sf::Vector2f(500, 350));
	//Initialize physics attributes
	m_moveSpeed =		1000;				//Pixels per second
	m_maxMoveSpeed =	1000;				//Pixels per second
	m_mass =			2.0f;
	m_velocity =		sf::Vector2f(0, 0);
	//Friction variables
	normalForce =		1.0f;
	frictionCoeff =		5.0f;
	m_friction =		sf::Vector2f(0, 0);
}


Enemy::~Enemy()
{
}

void Enemy::Update(sf::RenderWindow * window, sf::Time* dt)
{
	//Reset acceleration so it doesn't add on itself
	m_accel = sf::Vector2f(0, 0);

	CalculateFriction();
	ApplyForce(m_friction);
	m_velocity += m_accel * dt->asSeconds();
	m_bbox.setPosition(m_bbox.getPosition() + m_velocity * dt->asSeconds());
}

void Enemy::Draw(sf::RenderWindow * window)
{
	window->draw(m_bbox);
}
