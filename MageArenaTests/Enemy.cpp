#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy(std::vector<std::shared_ptr<GameObject>>* p_vec)
{
	m_destroyed = false;
	m_collisiongroup = 3;					//Enemy group is 3
	m_collidablegroups = 22;				//Groups Enemy can collide with, 2^4 = 16, 2^2 = 4, and 2^1 = 2, spell, terrain, and player
	m_enemybody.setSize(sf::Vector2f(50, 50));
	m_enemybody.setOrigin(m_enemybody.getSize().x / 2, m_enemybody.getSize().y / 2);
	m_enemybody.setFillColor(sf::Color::Blue);
	m_enemybody.setPosition(sf::Vector2f(500, 350));
	m_bbox = m_enemybody.getGlobalBounds();
	m_prevbbox = m_bbox;
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
	m_prevbbox = m_bbox;
	m_enemybody.setPosition(m_enemybody.getPosition() + m_velocity * dt->asSeconds());
	m_bbox = m_enemybody.getGlobalBounds();
}

void Enemy::Draw(sf::RenderWindow * window)
{
	window->draw(m_enemybody);
}
