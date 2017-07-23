#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy(std::vector<std::shared_ptr<GameObject>>* gameObjVector)
{
	m_destroyed = false;
	m_collisionGroup = 3;					//Enemy group is 3
	m_collidableGroups = 22;				//Groups Enemy can collide with, 2^4 = 16, 2^2 = 4, and 2^1 = 2, spell, terrain, and player
	m_enemyBody.setSize(sf::Vector2f(50, 50));
	m_enemyBody.setOrigin(m_enemyBody.getSize().x / 2, m_enemyBody.getSize().y / 2);
	m_enemyBody.setFillColor(sf::Color::Blue);
	m_enemyBody.setPosition(sf::Vector2f(500, 350));
	m_boundingBox = m_enemyBody.getGlobalBounds();
	m_previousBoundingBox = m_boundingBox;
	//Initialize physics attributes
	m_moveSpeed =		1000;				//Pixels per second
	m_maxMoveSpeed =	1000;				//Pixels per second
	m_mass =			2.0f;
	m_velocity =		sf::Vector2f(0, 0);
	//Friction variables
	m_normalForce =		1.0f;
	m_frictionCoeff =		5.0f;
	m_friction =		sf::Vector2f(0, 0);
}


Enemy::~Enemy()
{
}

void Enemy::update(sf::RenderWindow * window, sf::Time* dt)
{
	//Reset acceleration so it doesn't add on itself
	m_accel = sf::Vector2f(0, 0);

	calculateFriction();
	applyForce(m_friction);
	m_velocity += m_accel * dt->asSeconds();
	m_previousBoundingBox = m_boundingBox;
	m_enemyBody.setPosition(m_enemyBody.getPosition() + m_velocity * dt->asSeconds());
	m_boundingBox = m_enemyBody.getGlobalBounds();
}

void Enemy::draw(sf::RenderWindow * window)
{
	window->draw(m_enemyBody);
}
