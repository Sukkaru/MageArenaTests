#include "stdafx.h"
#include "Player.h"


Player::Player()
{
	m_playerBody.setSize(sf::Vector2f(50, 50));
	m_playerBody.setFillColor(sf::Color::Red);
	m_aimer.setFillColor(sf::Color::Blue);
	m_moveSpeed = 1000;
	m_mass = 2.0f;
	m_upForce = sf::Vector2f(0, -m_moveSpeed);
	m_downForce = sf::Vector2f(0, m_moveSpeed);
	m_rightForce = sf::Vector2f(m_moveSpeed, 0);
	m_leftForce = sf::Vector2f(-m_moveSpeed, 0);
	normalForce = 1.0f;
	frictionCoeff = 0.5f;
}


Player::~Player()
{
}

void Player::Update(sf::RenderWindow* window, sf::Clock* clock)
{
	sf::Time dt = clock->restart();
	m_accel = sf::Vector2f(0, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		ApplyForce(m_downForce);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		ApplyForce(m_upForce);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		ApplyForce(m_leftForce);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		ApplyForce(m_rightForce);
	}
	//if (m_accel.x == 0 && m_accel.y == 0)
	
		//sf::Vector2f drag = m_friction * m_velocity * dt.asSeconds();
		//m_velocity -= drag;
	
		
		float frictionMag = frictionCoeff * normalForce;
		m_friction = m_velocity;
		m_friction *= -1.f;
		m_friction *= frictionMag;
		printf("Friction.x:%f\nFriction.y:%f\n", m_friction.x, m_friction.y);
		ApplyForce(m_friction);
		m_velocity += m_accel * dt.asSeconds();
		printf("Accel.x:%f\nAccel.y:%f\n", m_accel.x, m_accel.y);
		printf("Velocity.x:%f\nVelocity.y:%f\n", m_velocity.x, m_velocity.y);
		m_playerBody.setPosition(m_playerBody.getPosition() + m_velocity * dt.asSeconds());
		//printf("Position.x:%f\nPosition.y:%f\n", m_playerBody.getPosition().x, m_playerBody.getPosition().y);
}

void Player::Draw(sf::RenderWindow* window)
{
	window->draw(m_playerBody);
}



